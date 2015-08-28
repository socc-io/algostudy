#include<iostream>

using namespace std;

long long int number[10][1001] = {0};
int origin[4][3]={1,2,3,4,5,6,7,8,9,0,-1,-1};

void sum(int n){			// 길이 N 에 대한 각 번호의 경우의 수 합 구하기
	long long int S = 0;
	for(int i=0;i<10;i++){
		S += number[i][n];
	}
	
	cout<<S%1234567<<endl;
}
int main(){
	for(int i=0;i<=9;i++){			//길이 N 이 1 일 때,
		number[i][0] = 1;
	}	


	for(int j=1;j<1000;j++){					//길이 N 이 1000 까지의 경우의 수를 구한다.
		for(int p=0;p<4;p++){					
			for(int q=0;q<3;q++){
				int v = origin[p][q];
				if(v>=0){
					int num;
					if(origin[p-1][q]>=0 && p-1>=0){
						num = origin[p-1][q];
						number[v][j] += number[num][j-1];
						number[v][j] %= 1234567;
					}
					if(origin[p+1][q]>=0 && p+1<4){
						num = origin[p+1][q];
						number[v][j] += number[num][j-1];
						number[v][j] %= 1234567;
					}
					if(origin[p][q-1]>=0 && q-1>=0){
						num = origin[p][q-1];
						number[v][j] += number[num][j-1];
						number[v][j] %= 1234567;
					}
					if(origin[p][q+1]>=0 && q+1<3){
						num = origin[p][q+1];
						number[v][j] += number[num][j-1];
						number[v][j] %= 1234567;
					}
				}
			}
		}
	}

	int testcase,N;
	cin>>testcase;
	for(int tc=1;tc<=testcase;tc++){
		cin>> N;

		sum(N-1);
	}


}