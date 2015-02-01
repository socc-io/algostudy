	#include<iostream>

	using namespace std;

	int A[1000000]={0};
	int main(){
		int n,i,tmp;
		cin>>n;
		for(i=0;i<n;i++){
			cin>>tmp;
			A[tmp] = A[tmp-1]+1;
		}
		int M = 0;
		for(i=0;i<n;i++){
			if(A[i]>M){
				M = A[i];
			}
		}
		cout<<M<<endl;
	}