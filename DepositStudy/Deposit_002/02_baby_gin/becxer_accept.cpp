#include <fstream>
#include <iostream>
#define SIZE 6
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;
 
char* INPUT_TEXT =  "test.in";
char* OUTPUT_TEXT = "test.out";
 
int card[SIZE];
int count[10] = {0};
int cc = 6;
int solution(istream& in, ostream& out){
     for(int i = 0; i < SIZE ; i++){
        in >> card[i];
        count[card[i]]++;
    }
    for(int i = 0; i < 10 ; i++){
        if(count[i] >= 3){
            int cl = 0;
            for(int j = 0 ; j < SIZE ; j++){
                if(card[j] == i) {
                    cl++;
                    card[j] = -1;
                    cc-=1;
                    if(cl >= 3) break;
                }
            }
            count[i] -= 3;
        }
    }
 
    for(int i = 0; i < 10 ; i++){
        if(count[i] >= 3){
            int cl = 0;
            for(int j = 0 ; j < SIZE ; j++){
                if(card[j] == i) {
                    cl++;
                    card[j] = -1;
                    cc-=1;
                    if(cl >= 3) break;
                }
            }
            count[i] -= 3;
        }
    }
 
    for(int i = 0; i < 8 ; i++){
        if(count[i] >= 1 && count[i+1] >=1 && count[i+2] >= 1){
            count[i]--; count[i+1]--; count[i+2] --;
            cc -= 3;
        }
    }
 
    for(int i = 0; i < 8 ; i++){
        if(count[i] >= 1 && count[i+1] >=1 && count[i+2] >= 1){
            count[i]--; count[i+1]--; count[i+2] --;
            cc -= 3;
        }
}
 
    if(cc!=0){
        out << "lose" << endl;
    }else{
        out << "gin" << endl;
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
