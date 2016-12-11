#!/bin/bash
echo "making problem number...$1"
touch $1.cpp
touch $1.input.txt
touch $1.compile_run.sh
chmod 777 $1.compile_run.sh
echo "#!/bin/bash" >> $1.compile_run.sh
echo "g++ $1.cpp -o $1.out" >> $1.compile_run.sh
echo "./$1.out < $1.input.txt" >> $1.compile_run.sh
