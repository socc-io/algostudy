#include <fstream>
#include <iostream>
#define VERSION "FILE"

using namespace std;

class Node{
public:
	bool isFull;
	int start, end;
	Node* left;
	Node* right;
	Node* parent;
	Node(int s, int e) :start(s), end(e), isFull(false){}
};

Node* root;

void makeSegmentTree(Node* parent){
	int s = parent->start; int e = parent->end;
	parent->left = new Node(s, (s+e)/2);
	parent->right = new Node((s+e)/2, e);
	parent->left->parent = parent;
	parent->right->parent = parent;
	if (s != (s + e) / 2) makeSegmentTree(parent->left);
	if (e != (s + e) / 2) makeSegmentTree(parent->right);
}

void insertTree(Node* dest, int start, int end){
	int ls = dest->left->start; int le = dest->left->end;
	int rs = dest->right->start; int re = dest->right->end;

	//범위에 따라서 나누는거 해야됨.

}

int sumFullNode(Node* dest){

}


int solution(istream& in, ostream& out){
	int W, Q, cmd, start, end;
	in >> W >> Q;
	root = new Node(0, W);
	makeSegmentTree(root);
	while (Q-- > 0){
		in >> cmd;
		if (cmd == 0){
			in >> start >> end;
			insertTree(root, start, end);
		}else if(cmd == 1){
			out << sumFullNode(root) << endl;
		}
	}
	return 0;
}


int main(void){
	istream* in = &cin;
	ostream* out = &cout;
	ifstream ifs; ofstream ofs;
	if (VERSION == "FILE"){
		ifs.open("poop.in");
		ofs.open("poop.out");
		in = &ifs; out = &ofs;
	}
	return solution(*in, *out);
}
