#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int left, right;
    scanf("%d%d", &left, &right);
    if(left < 1) left = 1;
    int size = right - left + 1;
    vector<int> arr(size, 0);
    int right_h = (right >> 1);

    if(left == 1) {
        arr[0] = 1;
    } else if(left == 0) {
        arr[0] = 1;
        arr[1] = 1;
    }

    for(int fb=2; fb <= right_h; ++fb) {
        bool inrange = (left <= fb);
        if(inrange && arr[fb - left] == 1) continue;
        int start = fb - (left % fb);
        start = (start == fb ? 0 : start) + left;
        if(start <= fb) start = (fb << 1);
        for(int fc = start; fc <= right; fc += fb) {
            arr[fc - left] = 1;
        }
    }

    for(int i=0; i<size; ++i) {
        if(arr[i] == 0) {
            printf("%d\b", i + left);
        }
    }
}

