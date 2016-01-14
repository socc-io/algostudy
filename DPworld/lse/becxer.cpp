#include <iostream>

using namespace std;

class lines{
public:
    int count;
    int s[81],e[81];
    void print(){
        for(int i = 0 ; i < count ; i++){
            cout << "[" << s[i] << "," << e[i] << "]-";
        }
        cout << endl;
    }
    
    lines(int new_s, int new_e){
        s[count] = new_s;
        e[count++] = new_e;
    }
    
    lines(lines* l, int new_s, int new_e){
        for(int i = 0 ; i < l->count ; i++){
            this->s[i] = l->s[i];
            this->e[i] = l->e[i];
        }
        this->count = l->count;
        s[count] = new_s;
        e[count++] = new_e;
    }

    bool check_valid(int new_s, int new_e){
        for(int i = 0 ; i < count ; i++){
            if(!(e[i] <= new_s || s[i] >= new_e))
                return false;
        }
        return true;
    }
};

lines* arr[1000000];
int len = 0;

int max_count = 0;
int max_count_count = 0;

int main(void){
    int n,s,e;
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        cin >> s >> e;
        if( s > e ){
            int temp = s;
            s = e;
            e = temp;
        }
        for(int j = len - 1 ; j >= 0 ; j--){
            if ( arr[j]->check_valid(s,e) ){
                arr[len++] = new lines(arr[j],s,e);
                if (max_count < arr[len-1]->count){
                   max_count = arr[len-1]->count;
                   max_count_count = 1;
                }else if( max_count == arr[len-1]->count ){
                   max_count_count += 1;
                }
            }
        }
        arr[len++] = new lines(s,e);
        if (max_count < arr[len-1]->count){
           max_count = arr[len-1]->count; 
           max_count_count = 1;
        }else if( max_count == arr[len-1]->count ){
           max_count_count += 1;
        }
    }
    cout << n-max_count << " "<< max_count_count << endl;
    return 0;
}
