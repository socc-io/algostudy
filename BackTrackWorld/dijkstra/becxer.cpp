#include <iostream>

using namespace std;
int line[1001][1001];
int line_index[1001][1001];
int line_count[1001];
int N, M, S;

class way{
public:
    int point[1001];
    int count_p;
    int length;
    
    way(int start){
        count_p = 1;
        length = 0;
        point[0] = start;
    }

    way(way* prev, int new_point){
        count_p = prev->count_p;
        for(int i = 0 ; i < prev->count_p ; i++){
             point[i] = prev->point[i];
        }
        int last_point = point[count_p-1];
        length = prev->length + line[last_point][new_point];
        point[count_p++] = new_point;
    }

    void print_way(){
        for(int i = 0 ; i < count_p ; i++){
            cout << point[i] << " ";
        }
        cout << endl;
    }
};


way* heap[1000001];
int heap_count = 0;
void push(way* w){
    heap[heap_count++] = w;
}

way* wayto[1001];
int wayto_count = 0;

way* pop(){
    int min_index = 0;
    int min_length = 9999999;
    for(int i = 0; i < heap_count ; i++){
        if ( heap[i]->length < min_length ) {
            min_length = heap[i]->length;
            min_index = i;
        }
    }
    way* res = heap[min_index];
    heap[min_index] = heap[heap_count-1];
    heap_count -= 1;
    return res;
}

int main(void){
    cin >> N >> M >> S;
    for(int i = 0; i <= N; i++){
        line_count[i] = 0;
        wayto[i] = NULL;
    }
    
    for(int i = 0; i < M ; i++){
        int f,t,l;
        cin >> f >> t >> l;
        line_index[f][line_count[f]++] = t;
        line[f][t] = l;
    }

    way* first_way = new way(S);
    push(first_way);

    while(true){

        way* now = pop();
        int last = now->point[now->count_p-1];

        if(wayto[last] == NULL){
            wayto[last] = now;
            wayto_count++;
        }

        if(wayto_count == N) break;

        for(int i = 0 ; i < line_count[last] ; i++){
            int next = line_index[last][i];
            if(wayto[next] == NULL){
                way* new_way = new way(now, next);
                push(new_way);
            }
        }
    }

    for(int i = 1 ; i <= N ; i++){
        wayto[i]->print_way();
    }

    return 0;
}
