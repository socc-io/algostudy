#include <stdio.h>
#include <string.h>

const int OPE = 19283;

int calculate(int *arr, int len)
{
	if((len & 1) == 0) {
		return OPE;
	}
	int done;
	while(len > 1) {
		done = false;
		for(int opIdx=1; opIdx<len; opIdx += 2) {
			if(arr[opIdx] == '*') {
				arr[opIdx-1] = arr[opIdx-1] * arr[opIdx+1];
				for(int i=opIdx; i<len-2; ++i) {
					arr[i] = arr[i+2];
				}
				len -= 2;
				done = true;
				break;
			}
			else if(arr[opIdx] == '/') {
				arr[opIdx-1] = arr[opIdx-1] / arr[opIdx+1];
				for(int i=opIdx; i<len-2; ++i) {
					arr[i] = arr[i+2];
				}
				len -= 2;
				done = true;
				break;
			}
		}
		if(done) continue;
		if(len <= 1) break;
		int opIdx = 1;
		if(arr[opIdx] == '+') {
			arr[opIdx-1] = arr[opIdx-1] + arr[opIdx+1];
			for(int i=opIdx; i<len-2; ++i) {
				arr[i] = arr[i+2];
			}
			len -= 2;
			done = true;
			break;
		}
		else if(arr[opIdx] == '-') {
			arr[opIdx-1] = arr[opIdx-1] - arr[opIdx+1];
			for(int i=opIdx; i<len-2; ++i) {
				arr[i] = arr[i+2];
			}
			len -= 2;
			done = true;
			break;
		}
		else {
			return OPE;
		}
	}
	return arr[0];
}

int main(int argc, char** argv)
{
	char str[2000];
	int arr[2000];
	int arrsize = 0;
	scanf("%s", str);
	int lenstr = strlen(str);
	int stoi = 0;
	int stoing = false;
	for(int chidx=0;chidx<lenstr;++chidx) {
		char ch = str[chidx];
		if('0' <= ch && ch <= '9') {
			stoing = true;
			stoi = stoi * 10 + (ch - '0');
		}
		else if(ch == '(') {
			arr[arrsize++] = OPE;
			if(stoing) {
				printf("ROCK");
				return 0;
			}
		}
		else if(ch == ')') {
			if(stoing) {
				arr[arrsize++] = stoi;
				stoi = 0;
				stoing = false;
			}
			else {
				printf("ROCK");
				return 0;
			}
			int opeIdx;
			for(opeIdx=arrsize-1; opeIdx >= 0; --opeIdx) {
				if(arr[opeIdx] == OPE) break;
			}
			opeIdx++;
			int local_len = arrsize - opeIdx;
			stoi = calculate(arr + opeIdx, local_len);
			if(stoi == OPE) {
				printf("ROCK");
				return 0;
			}
			stoing = true;
			arrsize -= local_len + 1;
		}
		else {
			if(stoing) {
				arr[arrsize++] = stoi;
				stoi = 0;
				stoing = false;
			}
			else {
				printf("ROCK");
				return 0;
			}
			arr[arrsize++] = ch;
		}
	}
	if(stoing) {
		arr[arrsize++] = stoi;
		stoi = 0;
		stoing = false;
	}
	int result = calculate(arr, arrsize);
	if(result == OPE) {
		printf("ROCK");
		return 0;
	}
	printf("%d\n", result);
	return 0;
}