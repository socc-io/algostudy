#include <iostream>

using namespace std;


class quiz{
public:
    int point,time;
    quiz(int p, int t):point(p),time(t) {}
};

int mp[10001] = {0,}; // max point, index is time
quiz* qs[10001]; // quiz seq

int main(void){
    int limit, n, p, t, max_p;
    cin >> limit >> n;

    for(int i = 0 ; i < n ; i++){
        cin >> p >> t;
        qs[i] = new quiz(p,t);
    }

    max_p = 0;
    for(int time = 0 ; time <= limit ; time++){
        for(int qi = 0 ; qi < n ; qi++){
            int before = time - qs[qi]->time;
            if(before >= 0){
                int temp = mp[before] + qs[qi] -> point;
                mp[time] = (mp[time] < temp)? temp : mp[time];
                max_p = (max_p < mp[time])? mp[time] : max_p;
            }
        }
    }

    cout << max_p << endl;
    return 0;
}
