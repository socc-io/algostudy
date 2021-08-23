#include <bits/stdc++.h>
using namespace std;

struct Node {
	vector<Node*> children;
	vector<pair<char, int>> index;
	int value;
	int sorted;
	Node * find(char ch) {
		if (sorted == 0) {
			sort(index.begin(), index.end());
			sorted = 1;
		}
		auto it = lower_bound(index.begin(), index.end(), make_pair(ch, 0));
		if (it != index.end() && it->first == ch) return children[it->second];
		return 0;
	}
	void set(char ch, Node * node) {
		index.push_back(make_pair(ch, children.size()));
		children.push_back(node);
		sorted = 0;
	}
} ns[8000000];
int nsi;

Node * alloc() {
	return ns + (nsi++);
}

struct Trie {
	Node * head;
	Trie() {
		head = alloc();
	}
	void insert(string & s, int value = 1) {
		Node * cur = head;
		for (char ch: s) {
			cur = get(cur, ch);
		}
		cur->value = value;
	}
	Node * get(Node * node, char ch) {
		Node * next = node->find(ch);
		if (next == 0) {
			Node * n = alloc();
			node->set(ch, n);
			return n;
		}
		return next;
	}
	vector<int> query(const string & s, int value = 1) {
		vector<int> res;
		int len = 0;
		Node * cur = head;
		for (char ch: s) {
			cur = cur->find(ch);
			if (cur == 0) return res;
			++len;
			if (cur->value == value) res.push_back(len);
		}
		return res;
	}
} ct, nt;

bool query(string & team) {
	auto c_lens = ct.query(team);
	reverse(team.begin(), team.end());
	auto n_lens = nt.query(team);
	sort(n_lens.begin(), n_lens.end());
	for (int c_len: c_lens) {
		int t_n_lens = team.size() - c_len;
		auto it = lower_bound(n_lens.begin(), n_lens.end(), t_n_lens);
		if (it == n_lens.end()) continue;
		if (*it == t_n_lens)
			return true;
	}
	return false;
}

int main() {
	int c, n, q;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> c >> n;
	while (c--) {
		string color; cin >> color;
		ct.insert(color);
	}
	while (n--) {
		string name; cin >> name;
		reverse(name.begin(), name.end());
		nt.insert(name);
	}
	cin >> q;
	while (q--) {
		string team; cin >> team;
		cout << (query(team) ? "Yes\n" : "No\n");
	}
	return 0;
}
