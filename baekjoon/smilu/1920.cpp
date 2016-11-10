#include <iostream>

using namespace std;

void merge_sort(int *arr, int len)
{
	int i,j,k;
	if(len < 16) { // selection sort
		for(i=0;i<len-1;++i) {
			int minval = arr[i];
			int minidx = i;
			for(j=i+1;j<len;++j) {
				int newval = arr[j];
				if(newval < minval) {
					minval = newval;
					minidx = j;
				}
			}
			if(i != minidx) {
				int tmp = arr[i];
				arr[i] = minval;
				arr[minidx] = tmp;
			}
		}
		return;
	}
	int f = len / 2;
	int *s = new int[len];

	merge_sort(arr,f);
	merge_sort(arr+f,len-f);

	for(i=0,j=f,k=0;i<f && j<len;) { // merge
		s[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	}
	while(i<f) s[k++] = arr[i++];
	while(j<len) s[k++] = arr[j++];

	for(int i=0;i<len;++i) arr[i] = s[i]; // copy

	delete[] s;
}

bool exists_check(int *arr, int arr_len, int findee)
{
	int left = 0;
	int right = arr_len-1;
	int mid = (left + right) / 2;
	int mid_val = arr[mid];
	while(mid_val != findee) {
		if(mid_val < findee) {
			left = mid;
			mid = (left + right) / 2;
			mid_val = arr[mid];
		}
		if(findee < mid_val) {
			right = mid;
			mid = (left + right) / 2;
			mid_val = arr[mid];	
		}
		if(left + 2 == right) {
			if(arr[left] != findee && mid_val != findee && arr[right] != findee) return false;
			else return true;
		}
		else if(left + 1 == right) {
			if(mid_val != findee && arr[right] != findee) return false;
			else return true;
		}
		else if(left == right) {
			if(mid_val != findee) return false;
			else return true;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	int arr_len;
	int *arr;
	int findee_len;
	int *findee;

	cin >> arr_len;
	arr = new int[arr_len];
	for(int i=0;i<arr_len;++i) {
		cin >> arr[i];
	}
	merge_sort(arr, arr_len);
	cin >> findee_len;
	findee = new int[findee_len];
	for(int i=0;i<findee_len;++i) {
		cin >> findee[i];
	}
	
	/*cout << "sorted : ";
	for(int i=0;i<arr_len;++i) cout << arr[i] << " ";
	cout << endl;*/

	for(int i=0;i<findee_len;++i) {
		if(exists_check(arr, arr_len, findee[i])) printf("1\n");
		else printf("0\n");
	}

	delete[] arr;
	delete[] findee;

	return 0;
}