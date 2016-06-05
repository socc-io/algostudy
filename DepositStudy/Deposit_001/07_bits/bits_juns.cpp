#include<iostream>

using namespace std;


long long int A[50];

void start(int cnt){
	long long int sum = 0;
	for(int i=0;i<=cnt;i++){
		sum+=A[i];
	}
	cout<<sum<<endl;
}
void combi(long long int n){//combination 
	A[0]=1;
	A[1]=n;
	long long int tmp=n;
	for(long long int i=2;i<=n;i++){
		if(i>n/2){
			A[i] = A[n-i];
			continue;
		}
		A[i]=A[i-1]*(--tmp)/i;
	}
	for(int i=0;i<=n;i++){
		cout<<A[i]<< " ";
	}
}
int main(){
	long long int n,cnt;
	cin>>n>>cnt;
	combi(n);
	start(cnt);
}