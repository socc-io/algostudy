#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

typedef unsigned long long llu;

#define INF ((1llu << 61) - 1)

int prior[3];
const int prior_size[] = {1, 61, 2};
int prior_position[3];
int n;
vector<llu> person;

/*
*  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
*/
int main()
{
	char buf[16];
	int pos = 64;
	for(int i=0; i<3; ++i) {
		int tmp;
		scanf("%d", &tmp);
		--tmp;
		prior_position[tmp] = pos - prior_size[tmp];
		pos -= prior_size[tmp];
	}
	scanf("%d", &n);
	person.resize(n, 0);
	for(int i=0; i<n; ++i) {
		llu pv[3] = { 0 };
		// gender
		scanf("%s", buf);
		if(buf[0] == 'F') pv[0] = 1;
		// age
		scanf("%llu", pv + 1);
		if(pv[1] <= 7) pv[1] = INF - pv[1];
		// disability
		if(getchar() != '\n') {
			scanf("%s", buf);
			if(!strcmp(buf, "PW")) pv[2] = 3;
			else if(!strcmp(buf, "DP")) pv[2] = 2;
			else if(!strcmp(buf, "P")) pv[2] = 1;
		}
		// mapping to bitmap
		for(int j=0; j<3; ++j) {
			person[i] |= (pv[j] << prior_position[j]);
		}
	}
	sort(person.begin(), person.end(), greater<llu>());
	for(int i=0; i<n; ++i) {
		llu gender = (person[i] >> prior_position[0]) & ((1llu << prior_size[0]) - 1);
		printf("%c ", gender ? 'F' : 'M');
		llu age = (person[i] >> prior_position[1]) & ((1llu << prior_size[1]) - 1);
		if(INF - 7 <= age) age = INF - age;
		printf("%llu ", age);
		llu disability = (person[i] >> prior_position[2]) & ((1llu << prior_size[2]) - 1);
		if(disability) {
			if(disability == 1) puts("P");
			else if(disability == 2) puts("DP");
			else if(disability == 3) puts("PW");
			else puts("error");
		} else puts("");
	}
}