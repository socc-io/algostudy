#!/bin/bash
#
# auto generate algorithm initial file and watching 
#
# @email becxer87@gmail.com
# @author becxer
#

if [ $# -lt 2 ]
then
	echo "usage: $0 title langauge"
	echo "support language : cpp, wincpp"
	exit
fi

title=$1
plang=$2
cmd=""
case "$plang" in
cpp|CPP|Cpp) python genCpp.py $title
			 cmd="python ./pydemon.py 'g++ $title.cpp -o $title.o;./$title.o < $title.input'"
	;;
wincpp) python genWinCpp.py $title
			cmd="python ./pydemon.py 'g++ $title.cpp -o $title.o;./$title.o $title.input'"
	;;
esac

eval $cmd
