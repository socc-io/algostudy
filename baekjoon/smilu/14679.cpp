#include <cstdio>

#define INF 0x7FFFFFFF
#define MOD 1000000007

#define PILSAL_THRESHOLD 100000000

int strlen(char* s)
{
	for(char* ch = s; (*ch) != '\0'; ++ch); return ch - s;
}

unsigned int N;
unsigned int A, D, H;
unsigned int MA, MD, MH;
unsigned int Ap, Aa, Dp, Da, Hp, Ha;

inline int max(int a, int b)
{
	if(a < b) return b;
	return a;
}

int pow(int a, int b, int m)
{
	int res = 1;
	while(b) {
		if(b & 1) {
			res = (res * a) % m;
		}
		a = (a * a) % m;
		b >>= 1;
	}
	return res;
}

int main(void)
{
	scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d",
		&N,
		&A, &D, &H,
		&MA, &MD, &MH,
		&Ap, &Aa, &Dp, &Da, &Hp, &Ha);

	bool killable = true;
	bool pilsal = false;

	for(int mon_idx = 0; mon_idx < N; ++mon_idx) {

		if(A > MOD || H > MOD) { // MODING
			A -= MOD;
			H -= MOD;
		}

		if(!pilsal) {

			if(A > PILSAL_THRESHOLD || D > PILSAL_THRESHOLD || H > PILSAL_THRESHOLD) {
				pilsal = true;
			}

			int damage = max(A - MD, 1);
			int M_damage = max(MA - D, 1);

			if((MH + damage - 1) / damage > (H + M_damage - 1) / M_damage) {
				killable = false;
				break;
			}
		}

		A += MA;
		D += MD;
		H += MH;

		MA = ((pow(MA, Ap, 100) + Aa) % 100) + 1;
		MD = ((pow(MD, Dp, 3) + Da) % 3) + 1;
		MH = ((pow(MH, Hp, 1000) + Ha) % 1000) + 1;
	}

	if(killable) {
		printf("%d %d %d", A % MOD, D % MOD, H % MOD);
	} else {
		puts("-1");
	}

	return 0;
}