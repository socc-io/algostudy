#include<iostream>

using namespace std;

int A[100];
int B[100];
int C[100];
int M[100] = {4, 1, 2, 3, 4, 5, 1, 2, 1, 3}; 

void merge(int start, int end){
	if(start==end){return;}
	int mid = (start+end)/2;
	int i=0,j=0,k=0;
	int X[50]={0};int Y[50]={0};

	for(i=start;i<=end;i++){
		if(i<=mid){
			X[j] = M[i];
			j++;		
		}
		else{
			Y[k] = M[i];
			k++;	
		}
	}
	i=start;
	j=0,k=0;
	while(i<=end){
		if(X[j]<=Y[k]){
			C[i] = X[j];j++;
	
			if(X[j]==0){
				j=-1;
				break;
			}
		}
		else{
			C[i] = Y[k];k++;
			if(Y[k]==0){
				k=-1;
				break;
			}
		}
		i++;
	}
	i++;	
	
	if(k==-1){
		for(i;i<=end;i++){
			C[i] = X[j];j++;
		}
	}
	else{
		for(i;i<=end;i++){
			C[i] = Y[k];k++;
		}
	}
	for(i=start;i<=end;i++){
		M[i] = C[i];
	}
}
int count = 0;
void make_Merge(int M[], int start , int end){
	int mid = (start+end)/2;

	if(start<end){
		make_Merge(M,start,mid);
		make_Merge(M,mid+1,end);
	}

	merge(start,end);

}

//4 1 2 3 4 5 1 2 1 3

int main(){
	make_Merge(M,0,10);
	for(int i=0;i<=10;i++){
		cout<<M[i]<<" ";
	}cout<<endl;
}