#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<int> a = {1,2,2, 3, 3, 3, 4};
    a.erase(unique(a.begin(), a.end()), a.end());
    for(int i=0; i<a.size(); ++i) {
        printf("%d ", a[i]);
    }
}
