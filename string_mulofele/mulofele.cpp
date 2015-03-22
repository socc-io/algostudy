#include<iostream>
#include<string.h>
using namespace std;

int main(){
	char eleven[305];
	cin>>eleven;

	int size = strlen(eleven);

	int a =  eleven[0]-'0';
	int i=0;
	while(true){
		if(i==size-1){
			break;
		}
		a*=10;
		a+=(eleven[++i]-'0');
		if(a>=11){
			a%=11;
		}
	}
	if(!a){
		cout<<"yes"<<endl;
	}
	else{cout<<"no"<<endl;}

}