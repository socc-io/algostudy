#include <fstream>
#include <iostream>
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;

char* INPUT_TEXT =  "upstair.input";
char* OUTPUT_TEXT = "upstair.output";

int way[100];
int solution(istream& in, ostream& out){
    int N;
    in >> N;
    way[0] = 1;
    way[1] = 2;
    for(int i = 2 ; i < N ; i++){
        way[i] = way[i-1]+ way[i-2];
    }
    out << way[N-1] <<endl;
    return 0;
}

int main(int argc, char* argv[]){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;

    if (VERSION == "ARGV"){
        if(argc != 2) {
            cout << "upstair.out upstair.input" << endl;
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
