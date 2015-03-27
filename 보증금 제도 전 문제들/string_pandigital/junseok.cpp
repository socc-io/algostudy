#include<iostream>
#include<string.h>
using namespace std;

int main(){
	char A[11];
	cin>>A;
	bool check[11]={false};
	int size = strlen(A);

	int i=0;
	while(i!=size){
		if(check[A[i]-'0']==false&&(A[i]-'0')<=size&&(A[i]-'0')>0){
			check[A[i]-'0'] = true;
		}
		else{
			cout<<"no"<<endl;
			return 0;
		}
		i++;
	}
	cout<<"yes"<<endl;
	return 0;

}