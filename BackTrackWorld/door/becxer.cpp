#include <iostream>

using namespace std;

template <typename T> 
class QUEUE {
public:
    T* arr[100000];
    int start,top;
    QUEUE(){ start = 0; top = 0; }
    void push(T* a){ arr[top++] = a; }
    T* front(){ return arr[start++]; }
    bool isEmpty(){ return start == top; }
};

class DoorStatus {
public:
    int a,b;
    int mc;
    DoorStatus(int a, int b, int mc):a(a),b(b),mc(mc){}
};

int abs(int a){
    return (a>0)? a:-a;
}

int main(void){
    int d,a,b,sn,seq;
    cin >> d >> a >> b >> sn;
    if( a > b ){ int temp; temp = a; a = b; b = temp;}
    
    DoorStatus* first_ds = new DoorStatus(a,b,0);
    QUEUE<DoorStatus> q = QUEUE<DoorStatus>();
    q.push(first_ds);
    
    QUEUE<DoorStatus> desk = QUEUE<DoorStatus>();
    for(int i = 0 ; i < sn ; i++){
        cin >> seq;
        while(!q.isEmpty()){
            desk.push(q.front());      
        }

        while(!desk.isEmpty()){
            DoorStatus* now = desk.front();
            if( seq > now->a ){
                q.push(new DoorStatus(now->a, seq, now->mc + abs(seq-now->b)));
            }
            if( seq < now->b ){
                q.push(new DoorStatus(seq, now->b, now->mc + abs(seq-now->a)));
            }
        }
    }

    int min = 999999;
    while(!q.isEmpty()){
        DoorStatus* ds = q.front();
        min = (min > ds->mc)? ds->mc : min;
    }
    cout << min << endl;
    return 0;
}
