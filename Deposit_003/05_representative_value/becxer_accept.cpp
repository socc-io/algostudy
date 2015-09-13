#include <fstream>
#include <iostream>
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;
 
char* INPUT_TEXT =  "NumCount.input";
char* OUTPUT_TEXT = "NumCount.output";
 
int arr[10];
int sum;
int solution(istream& in, ostream& out){
    for(int i = 0 ; i < 5 ; i++ ) {
        in >> arr[i]; sum+=arr[i];
    }
    for(int i = 0 ; i < 5 ; i++){
        for(int j = i ; j < 5 ; j++){
            if(arr[j] > arr[i]){
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    out << sum /5 << endl;
    out << arr[2] << endl;
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
