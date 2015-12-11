#include <iostream>

using namespace std;

int main(){
	
	int p = 0;
	int* s = NULL;
	
	int answer = 0;
	int prev = 0;
	bool prev_eat = false;
	int current = 0;
	int minimum = 0;
	cin >> p;
	for(int i=0; i<p; i++){
		cin >> current;
		if(current > prev){
			if(prev_eat)
				answer = answer - prev + current;
			else
				answer = answer - minimum + current;
			prev_eat = true;
			minimum = 500;
		} else {
			if( current < minimum )
				minimum = current;
			prev_eat = false;
		}
		prev = current;
	}
	
	cout << answer;
	
	return 0;
}
