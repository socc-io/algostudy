#include <iostream>

using namespace std;

class Node{
public:
	bool isFull;
	int start, end;
	Node* left;
	Node* right;
	Node* parent;
	Node(int s, int e) :start(s), end(e){}
};

Node* root;
Node* makeTree(int start, int end){
	//재귀로?!
}

void insertTree(Node* dest, int start, int end){
	
}

int sumFullNode(Node* dest){

}

int main(void){
	int W, Q;
	cin >> W >> Q;
	root = new Node(0, 8);

	return 0;
}
