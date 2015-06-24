#!/usr/bin/python
#
# @ email becxer87@gmail.com
# @ author becxer
#

import sys
template = '''
#include <fstream>
#include <iostream>
#define VERSION "ARGV" //FILE, STDIN, ARGV
using namespace std;

char* INPUT_TEXT =  "#title.input";
char* OUTPUT_TEXT = "#title.output";

int solution(istream& in, ostream& out){
	char test[100];
	in >> test;
	out << test;

    return 0;
}

int main(int argc, char* argv[]){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;

    if (VERSION == "ARGV"){
        if(argc != 2) {
            cout << "#title.out #title.input" << endl;
            return 0;
        }
        INPUT_TEXT = argv[1];
        ifs.open(INPUT_TEXT);
        in = &ifs;
    }

    if (VERSION == "FILE"){
        ifs.open(INPUT_TEXT);
        ofs.open(OUTPUT_TEXT);
        in = &ifs; out = &ofs;
    }
    return solution(*in,*out);
}
'''


if len(sys.argv) <= 1:
	print ''
	print 'usage : genAlgoSource.py "problem_title" TYPE (default : ARGV)'
	print ''
	print 'TYPE : ARGV -> input from file, output to stdout (default)'
	print 'TYPE : STDIN -> input from stdin, output to stdout'
	print 'TYPE : FILE -> input from file, output to file'
	print ''
	exit()

title = sys.argv[1]
if len(sys.argv) >= 3:
	template = template.replace("ARGV",sys.argv[2])
template = template.replace("#title",title)
f = open(title+".cpp","w")
f.write(template)
f.close()
f = open(title+".input","w")
f.write("hello-algostudy!")
f.close()
print title + '.cpp ' + title + '.input generated'
