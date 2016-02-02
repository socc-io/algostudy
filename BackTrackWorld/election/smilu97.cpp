#include <stdio.h>
#include <vector>
using namespace std;
#pragma warning(disable:4996)
typedef pair<int, int> position;
char map[5][5];
char road[5][5];
position roadstack[25];
int index_roadstack = 0;
int alreadyRoad[8][10000];
int index_alreadyRoad[7];
position jpos[25];
int jposnum = 0;
int Count = 0;
int blockcount = 0;

//void printonly() {
//	for (int i = 0; i < 5; ++i) {
//		bool check;
//		int iter[5];
//		int index_iter = 0;
//		for (int j = 0; j < 5; ++j) {
//			check = false;
//			for (int k = 0; k < index_roadstack; ++k) {
//				if (roadstack[k].first == i && roadstack[k].second == j) {
//					check = true;
//					iter[index_iter++] = k;
//					break;
//				}
//			}
//			if (check) {
//				printf("%c", map[i][j]);
//			}
//			else {
//				printf(".");
//			}
//		}
//		printf("   ");
//		int c = 0;
//		for (int j = 0; j < 5; ++j) {
//			check = false;
//			for (int k = 0; k < index_roadstack; ++k) {
//				if (roadstack[k].first == i && roadstack[k].second == j) {
//					check = true;
//					break;
//				}
//			}
//			if (check) {
//				printf("%d", iter[c++]);
//			}
//			else {
//				printf(".");
//			}
//		}
//		printf("\n");
//	}
//	printf("\n");
//}

int RoadToInt() {
	int sum = 0;
	for (int i = 0; i < index_roadstack; ++i) {
		sum += 1 << roadstack[i].first * 5 + roadstack[i].second;
	}
	return sum;
}

void ref(int len, int jnum)
{
	int nextlen = len + 1;
	int nextjnum = jnum + 1;
	if (len == 0) {
		for (int i = 0; i < jposnum; ++i) {
			roadstack[index_roadstack++] = jpos[i];
			// alreadyRoad[0][index_alreadyRoad[0]++] = 1 << roadstack[0].first * 5 + roadstack[0].second;
			ref(nextlen, 1);
			--index_roadstack;
			
		}
	}
	else if (len == 7) {
		int thismapvalue = RoadToInt();
		for (int i = 0; i < index_alreadyRoad[7]; ++i) {
			if (alreadyRoad[7][i] == thismapvalue) {
				++blockcount;
				return;
			}
		}
		if (jnum > 3) { 
			Count++; 
			//printonly(); 
			alreadyRoad[7][index_alreadyRoad[7]++] = thismapvalue;
		}
	}
	else
	{
		int thismapvalue = RoadToInt();
		int *endi = &index_alreadyRoad[len];
		for (int i = 0; i < *endi; ++i) {
			if (alreadyRoad[len][i] == thismapvalue) {
				++blockcount;
				return;
			}
		}
		alreadyRoad[len][*endi] = thismapvalue;
		(*endi)++;
		bool togo[5][5];
		for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) togo[i][j] = false;
		for (int i = 0; i < index_roadstack; ++i) {
			position postmp = roadstack[i];
			if (0 < postmp.first) togo[postmp.first - 1][postmp.second] = true;
			if (postmp.first < 4) togo[postmp.first + 1][postmp.second] = true;
			if (0 < postmp.second) togo[postmp.first][postmp.second - 1] = true;
			if (postmp.second < 4) togo[postmp.first][postmp.second + 1] = true;
		}
		for (int i = 0; i < index_roadstack; ++i) {
			togo[roadstack[i].first][roadstack[i].second] = false;
		}
		for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) if (togo[i][j]) {
			roadstack[index_roadstack++] = position(i, j);
			ref(nextlen, map[i][j] == 'J' ? nextjnum : jnum);
			--index_roadstack;
		}
	}
}

int main(void)
{
	for (int i = 0; i < 5; ++i)
	{
		char str[6];
		scanf("%s", &str);
		for (int j = 0; j < 5; ++j)
		{
			map[i][j] = str[j];
			if (str[j] == 'J') {
				jpos[jposnum++] = position(i, j);
			}
		}
	}
	for (int i = 0; i < 7; ++i) index_alreadyRoad[i] = 0;
	ref(0, 0);
	//printf("Count : %d\nblockcount : %d\n", Count, blockcount);
	printf("%d\n", Count);
	return 0;
}