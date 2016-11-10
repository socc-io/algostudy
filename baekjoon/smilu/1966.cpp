#include <stdio.h>

int main(int argc, char** argv)
{
	int arr[10000];
	int docu_num;
	int obj_idx;
	int start, end;
	int T;
	scanf("%d", &T);
	for(int case_idx=0; case_idx<T; ++case_idx) {
		scanf("%d %d", &docu_num, &obj_idx);
		start = 0;
		end = docu_num;
		for(int i=0;i<docu_num;++i) {
			scanf("%d", &arr[i]);
		}
		int cnt = 0;
		while(start < end) {
			cnt++;
			int first = arr[start];
			bool biggerCheck = false;
			for(int i=start+1;i<end;++i) {
				if(first < arr[i]) {
					biggerCheck = true;
					break;
				}
			}
			if(biggerCheck) {
				if(start == obj_idx) obj_idx = end;
				arr[end++] = first;
				start++;
				continue;
			}
			start++;
			if(first == obj_idx) {
				printf("%d\n", cnt);
			}
		}
	}
	return 0;
}