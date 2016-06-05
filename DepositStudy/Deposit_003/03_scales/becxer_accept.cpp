
#include <fstream>
#include <iostream>
#define VERSION "STDIN" //FILE, STDIN, ARGV
using namespace std;

char* INPUT_TEXT =  "scales.in";
char* OUTPUT_TEXT = "scales.out";

int arr[100] = {0};
int count[1000] = {0};
int n,sum = 0;
int solution(istream& in, ostream& out){
	in >> n;
	for(int i = 0; i < n ; i ++){
		in >> arr[i];
		sum += arr[i];
	}
	if( sum %2 != 0 ) {
		out << "impossible" <<endl;
		return 0;
	}

	for(int i = 0; i < n ; i ++){
		for(int j = i ; j < n ; j++){
			if(arr[j] > arr[i]){
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
	}

	for(int i = 0; i < n ; i++){
		int temp[1000] = {0};
		temp[arr[i]]++;
		for(int j = 0 ; j < 301 ; j++){
			if(count[j] != 0){
				temp[j+arr[i]] += count[j];
			}
		}
		for(int j = 0 ; j < 301 ; j++){
			if(temp[j]  != 0){
				count[j] += temp[j];
			}
		}
	}
	
	if(count[sum/2]!= 0) out << count[sum/2] << endl;
	else out << "impossible" << endl;

    return 0;
}

int main(int argc, char* argv[]){
    istream* in = &cin; ostream* out = &cout;
    ifstream ifs; ofstream ofs;

    if (VERSION == "ARGV"){
        if(argc != 2) {
            cout << "scales.out scales.in" << endl;
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
