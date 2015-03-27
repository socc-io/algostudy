#include<iostream>

using namespace std;

void test(int n,int first, int second, int third){
	if(n<=0){
		return ;
	}
	test(n-1,first,third,second);
	cout<<first<<" "<<third<<endl;
	test(n-1,second,first,third);
}

int main(){
	int n;
	cin>>n;
	test(n,1,2,3);
}
