#include <stdio.h>

//¾È°ãÄ¡¸é ÃÑ 10ºÐ
//°ãÄ¡¸é °¢°¢ 10ºÐ
int main(){
	int start, end;
	int max = 0;
	int num;
	int temp;
	int total_time = 10;
	int count[401] = {0, };
	int s[201] = {0, }, t[201] = {0, };
	scanf("%d",&num);
	for(int i=0;i<num;i++){
		scanf("%d %d",&s[i],&t[i]);
		if(s[i] % 2 == 1)
			s[i]++;
		if(t[i] % 2 == 1)
			t[i]++;
		if(s[i] > t[i]){
			temp = s[i];
			s[i] = t[i];
			t[i] = temp;
		}
	}
	for(int i=1;i<num;i++){
		for(int j =0;j<i;j++){
			if(s[i] >= s[j] && s[i] <= t[j] || t[i] >= s[j] && t[i] <= t[j]){
				start = s[i] >= s[j] ? s[i] : s[j];
				end =   t[i] <= t[j] ? t[i] : t[j];
				//printf("%d = %d %d\n",i,start,end);
				for(int k = start ; k<= end;k++)
					count[k] ++;
				break;
			}
			
		}
	}
	for(int i=1;i<=400;i++){
		if(count[i] > max)
			max = count[i];
	}
	//printf("max = %d\n",max);
	printf("%d\n",(max*10)+10);
	return 0;
}