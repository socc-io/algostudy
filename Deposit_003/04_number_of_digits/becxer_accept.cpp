#include <fstream>
#include <iostream>
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;

char* INPUT_TEXT =  "NumCount.input";
char* OUTPUT_TEXT = "NumCount.output";

int count[10];
int get_oneplace(int n){
    if(n < 10) count[n]++;
    else {
        count[n % 10] ++;
        get_oneplace(n/10);
    }
    return 0;
}

int solution(istream& in, ostream& out){
    int A,B,C;
    in >> A >> B >> C;
    int res = A*B*C;
    get_oneplace(res);
    for(int i = 0 ; i < 10 ;i ++){
        out << count[i] << endl;
    }

    return 0;
}

int main(int argc, char* argv[]){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;

    if (VERSION == "ARGV"){
        if(argc != 2) {
            cout << "NumCount.out NumCount.input" << endl;
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
