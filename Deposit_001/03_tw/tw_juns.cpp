#include<iostream>

using namespace std;

int A[500001]={0};
int tw[500001]={0};
int tmp_h[500001]={0};
int tmp_index[500001]={0};
int top = 0;
int main(){
	int n;cin>>n;
	int tmp=0;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		if(i==1){
			tmp_h[top]=A[i];
			tmp_index[top]=i;
			top++;
		}
		if(A[i]<A[i-1]){	//바로 전 높이보다 작을 때 스택배열에 저장
			tw[i]=i-1;
			tmp_h[top] = A[i-1];
			tmp_index[top]= i-1;
			top++;
		}
		else{			//스택배열 뒤지기
			tmp = top-1;
			while(tmp>=0){
				if(tmp_h[tmp]>A[i]){
					tw[i]=tmp_index[tmp];
					break;
				}
				tmp--;
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<tw[i]<<" ";
	}cout<<endl;

}