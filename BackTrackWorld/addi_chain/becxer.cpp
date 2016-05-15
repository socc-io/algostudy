#include <iostream>
#define MAX_QUEUE 1000000

using namespace std;

class chain{
public:
    int arr[201];
    int count;
    chain(){arr[0]=1;count=1;}
    chain(chain* other, int new_num){
        for(int i = 0; i < other->count ; i++){
            this->arr[i] = other->arr[i];
        }
        this->count = other->count;
        this->arr[count++] = new_num;
    }
    void print(){
        for(int i = 0 ; i < count ; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    bool isGoal(int n){
        return (arr[count-1] == n)? 1 : 
                ((arr[count-1] < n)? 0 : -1);
    }
};

//CIRCULAR QUEUE START
chain* queue[MAX_QUEUE];
int head = 0; int tail = 0;
bool isEmpty(){ return (head == tail)? true : false; }
bool push(chain* c){
    int next_tail = (tail + 1) % MAX_QUEUE;
    if(head != next_tail){
        queue[tail] = c;
        tail = next_tail;
        return true;
    }else{
        return false;
    }
}

chain* pop(){
    chain* res = queue[head];
    head = (head + 1) % MAX_QUEUE;
    return res;
}

//CIRCULAR QUEUE END
int main(void){
    int n;
    cin >> n;
    chain* first = new chain();
    push(first);

    while(!isEmpty()){
        chain* now = pop();
        now->print();
            for(int j = now->count-1; j >=0 ; j--){
                int new_num = now->arr[now->count-1] + now->arr[j];
                if(new_num <= now->arr[now->count-1]){
                    break;
                }else{
                    if(new_num < n){
                        chain* candy = new chain(now,new_num);
                        push(candy);
                    }else if(new_num == n){
                        chain* candy = new chain(now,new_num);
                        candy->print();
                        return 0;
                    }
                }
            }
        
    }
    return 0;
}
