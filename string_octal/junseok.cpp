#include<iostream>
#include<string.h>
using namespace std;

int main(){
	char octal[101];

	cin >> octal;

	int size = strlen(octal);
	int tmp=size%3;
	int i;
	int result=0;

	if(tmp==0){
		result+=(octal[0]-'0')*4+(octal[1]-'0')*2+octal[2]-'0';
		i=3;
	}
	else if(tmp==2){
		result+=(octal[0]-'0')*2+octal[1]-'0';
		i=2;
	}
	else if(tmp==1){
		result+=octal[0]-'0';
		i=1;
	}
	cout<<result;
	while(i<=size-1){
		result = (octal[i]-'0')*4+(octal[i+1]-'0')*2+octal[i+2]-'0';	
		cout<<result;
		i+=3;
	}
	return 0;
}