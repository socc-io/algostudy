#!/usr/bin/python
#
# use to run python program forever
# @author becxer
# @email becxer87@gmail.com
#
import signal
import sys
import subprocess
import time
import os
 
sleep_time = 1
bashCmd = ""
now_time = None

if len(sys.argv) == 1:
	print 'usage : pydemon.py "bash command or script.sh"'
	exit()
 
for i in range(len(sys.argv)):
	if i > 0 :
		if os.path.isfile(sys.argv[1]) and ('.sh' in sys.argv[1]):
			f = open(sys.argv[1],"r")
			bashCmd = f.read().replace('\n',';')
			f.close()
			break
		bashCmd += sys.argv[i] + " "

def set_now_time(path):
	global now_time
	dirs = os.listdir(path)
	for f in dirs:
		fnow = path+'/'+f
		if os.path.isdir(fnow) :
			set_filetime_last(fnow)
		elif os.path.getmtime(fnow) > now_time:
			now_time = os.path.getmtime(fnow)

def run_cmd(bashCmd):
	print "run [" + bashCmd + "]"
	process = subprocess.Popen(bashCmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
	output, error = process.communicate()
	print "[stderr]-----------------------"
	print error
	print "[stdout]----------------------"
	print output
	print "pydemon watching your directory..."
	return process.returncode

run_cmd(bashCmd)
set_now_time('./')
last_time = now_time 

while True:
	time.sleep(sleep_time)
	if last_time != now_time :
		status = run_cmd(bashCmd)
		set_now_time('./')
		last_time = now_time
		if status != 0 :
			print "[ERROR] process error"
	else :	
		set_now_time('./')	

