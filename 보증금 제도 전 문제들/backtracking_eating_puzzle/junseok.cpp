/*

40 6
7 13 17 19 29 31

*/
#include<iostream>

using namespace std;

int B[100001]={0};
int M=0;
int real_M=0;
void backtracking(int i, int c,int n, int sum){
	int S = sum + B[i];					

	if(S<=c){
		M=S;
		if(real_M<M){
			real_M=M;
		}
	}
	
	for(int j=i+1;j<=n;j++){
		backtracking(j,c,n,S);
	}

}
int main(){
	int c,i,n;
	cin>>c>>n;
	for(i=1;i<=n;i++){
		cin>>B[i];
	}

	for(i=1;i<=n;i++){
		M=0;
		backtracking(i,c,n,0);
	}
	cout<<real_M<<endl;;
}