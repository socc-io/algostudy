#include <cstdio>
#include <cstdlib>

char buf[100001];
int cnt[10];
int sum = 0;

// cnt를 보고 답을 출력
void print()
{
	int oup_idx = 0;
	for(int i=9; i>=0; --i) {
		char ch = '0' + i;
		for(int j=0; j<cnt[i]; ++j) {
			buf[oup_idx++] = ch;
		}
	}
	buf[oup_idx++] = '\0';
	if(buf[0] == '0') puts("-1");
	else puts(buf);
}

/*
 * start만큼 sum에서 빼기를 시도해서 0으로 만들기를 성공하면 출력
 */
void adjust(int start)
{
	// 뺐을 때 sum이 0이 되는 모든 수들을 시도
	for(int i=start; i<10; i+=3) {
		if(cnt[i] > 0) {  // 뺄 것이 있는지 확인
			--cnt[i];
			sum = (sum + 3 - i) % 3;
			if(sum == 0) {
				print();
				exit(1);
			}
		}
	}
}

int main(void)
{
	scanf("%s", buf);
	// 각 자리수를 모두 카운트
	for(char * pch = buf; *pch != '\0'; ++pch) {
		char ch = *pch;
		if('0' <= ch && ch <= '9') ++cnt[ch-'0'];
	}
	// 0이 없으면 실패
	if(cnt[0] == 0) {
		printf("-1");
		return 0;
	}
	// 각 자리수의 합을 3으로 나눈 나머지를 구함
	for(int i=1; i<10; ++i) {
		sum = (sum + i * cnt[i]) % 3;
	}
	// 3으로 나누어떨어졌다면 출력하고 끝
	if(sum == 0) {
		print();
		return 0;
	}
	// 나누어 떨어지지 않았다면 해당 수 만큼 빼기 시도
	adjust(sum);
	// 적당한 뺄 수가 없었다면 대체할 다른 수를 2개 빼기를 시도
	adjust(3-sum);
	adjust(sum);
	// 모두 실패했다면 -1 출력
	puts("-1");
	return 0;
}