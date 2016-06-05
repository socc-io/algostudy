#include <fstream>
#include <iostream>
#define INPUT_TEXT "test.in"
#define OUTPUT_TEXT "test.out"
#define VERSION "S" //FILE, STDIN
using namespace std;

int way[201] = {0,};

int cvt_room2way(int rnum){
    return (rnum % 2 == 0)? (rnum-1)/2 : rnum/2;
}

int solution(istream& in, ostream& out){
    int count,start,end,temp;
    int max = 0;
    in >> count;

    for(int i = 0 ; i < count ; i ++){
        in >> start >> end;
        start = cvt_room2way(start);
        end = cvt_room2way(end);
        if(start > end){
            temp = start;
            start = end;
            end = temp;
        }

        for(int j = start; j <= end ; j++){
            way[j] += 1;
        }
    }

    for(int i = 0 ; i < 200  ; i++){
        max = (max < way[i])? way[i] : max;
    }

    out << max * 10 << endl;
    return 0;
}

int main(void){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;
    if (VERSION == "FILE"){
        ifs.open(INPUT_TEXT);
        ofs.open(OUTPUT_TEXT);
        in = &ifs; out = &ofs;
    }
    return solution(*in,*out);
}
