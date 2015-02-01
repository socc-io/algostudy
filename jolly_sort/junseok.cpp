#include<iostream>
#include<algorithm>
using namespace std;

int A[25]={0};
int C[11]={0};
int D[11]={0};
int main(){
	int n,i,tmp;
	cin>>n;

	for(i=0;i<n;i++){
		cin>>A[i];	
	}
	int a,b;
	int index_a=0,index_b=0;
	i=0;
	a = n/2 + n%2;
	b = n/2;

	sort(A,A+n);

	while(i!=n){
		if(i<a){
			C[index_a++]=A[i];
		}
		else{
			D[index_b++]=A[i]; 
		}
		i++;
	}
	i=0;
	for(i=0;i<a;i++){
		cout<<C[i]<<" "<<D[i]<<endl;
	}cout<<endl;
	
	i=0;
	index_a=0,index_b=0;
	while(i!=n){
		if(i%2){
			A[i]=D[index_b++];
		}
		else{
			A[i]=C[index_a++];
		}
		i++;
	}
	for(i=0;i<n;i++){
		cout<<A[i]<<" ";
	}cout<<endl;
	
}