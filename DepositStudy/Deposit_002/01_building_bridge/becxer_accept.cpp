#include <fstream>
#include <iostream>
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;
 
char* INPUT_TEXT =  "test.in";
char* OUTPUT_TEXT = "test.out";
 
int val[100] = {0};
 
int solution(istream& in, ostream& out){
    int tc,r,n;
    in >> tc;
    while(tc --> 0){
        in >> r >> n;
        for( int i = r ; i <= n ; i++){
            if(i == r) val[i] = 1;
            else val[i] = i * val[i-1] / (i-r);
        }
        cout << val[n] << endl;
    }
    return 0;
}
 
int main(int argc, char* argv[]){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;
 
    if (VERSION == "ARGV"){
        if(argc != 2) {
            cout << "a.out input.txt" << endl;
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
