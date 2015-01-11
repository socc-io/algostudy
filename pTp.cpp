#include<iostream>
#include<string>
using namespace std;

void test(int n){
	if(n==1){
		cout<<n;
		return;
	}
	test(n-1);
	cout<<n;
	test(n-1); 
}
int main(){
	int n;
	cin>>n;
	test(n);
	cout<<endl;
}