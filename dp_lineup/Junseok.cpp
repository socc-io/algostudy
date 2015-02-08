	#include<iostream>

	using namespace std;

	int A[1000000]={0};
	int main(){
		int n,i,tmp,M = 0;
		
		cin>>n;
		for(i=0;i<n;i++){
			cin>>tmp;
			A[tmp] = A[tmp-1]+1;
			if(A[tmp]>M){
				M = A[tmp];
			}
		}
		cout<<n-M<<endl;
	}