#include <iostream>
 
using namespace std;
 
class meet{
  public:
  int start,end;
};
 
int main(void){
  int N; cin >> N; meet* arr[1001];
  for(int i = 0 ; i < N ; i++){
        arr[i] = new meet();
    cin >> arr[i]->start >> arr[i]->end;
  }
  for(int i = 0 ; i < N ; i++){
    for(int j = i ; j < N ; j++){
            if(arr[i]->end > arr[j]->end){
                      meet* temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
  }
 
  int last_end = 0;
  int count = 0;
  for(int i = 0 ; i < N ; i++){
    if(arr[i]->start >= last_end){
      last_end = arr[i]->end;
      count+=1;
    }
  }
 
  cout << count << endl;
  return 0;
}
