#include <stdio.h>

int cnt=1;
int player[1048577]={0, };
int temp[1048577]= {0, };
int win_play;
int answer=0;
void change(int addr, int S){
	player[addr] = S;
	for(int i=1;i<=cnt;i++ )
		temp[i] = player[i];
}
int winner(){
	int max=1;
	int i=1;
	for(i=1;i<=cnt;i++){
		if(player[max] < player[i]){
			max = i;
		}
	}
	return max;
}
int win_cnt(int i,int plus){
	if(i<2)
		return answer;
	int flag=1;
	int flag2 = 0;
	while(1){
		flag2 = 0;
		if(temp[flag] > temp[flag+plus]){
			temp[flag] = temp[flag];
		}
		else if(temp[flag] < temp[flag+plus]){
			temp[flag] = temp[flag+plus];
		}
		
		if(temp[flag] == player[win_play]){
			//printf("µå·ç¿Í");
			flag2 ++;
			answer ++;
		}
		flag= flag+(plus*2);
		
		if(flag == i || flag > i)
			break;
	}
	if(flag2 == 0)
		return answer;
	else
		win_cnt(i/2,plus*2);
}
int main(){
	int N,M;
	int addr,S;
	char order;
	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++){
		cnt*=2;
	}
	for(int i=1;i<=cnt;i++){
		scanf("%d",&player[i]);
		temp[i] = player[i];
	}
	for(int ii=0;ii<M;ii++){
		//printf("%d = ",ii);
		scanf(" %c",&order);
		switch(order){
		case 'R':
			scanf("%d %d",&addr,&S);
			change(addr, S);
			break;
		case 'W':
			printf("%d\n",winner());
			break;
		case 'S':
			scanf("%d",&win_play);
			answer = 0;
			win_cnt(cnt,1);
			if(answer > N)
				printf("%d\n",N);
			else
				printf("%d\n",answer);
			
			break;
		}
	}
	return 0;
}