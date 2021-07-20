#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* parent;
    map<int, Trie*> next;
    int value;
    int id;
    Trie(Trie* parent, int value): parent(parent), value(value), id(0) {}
    Trie* Find(int key) {
        auto it = next.find(key);
        if (it == next.end()) return 0;
        return it->second;
    }
    void Insert(int key, Trie* value) {
        next[key] = value;
    }
};

Trie* InsertSeq(Trie* head, int * arr, int len) {
    Trie * cur = head;
    for (int i = 0; i < len; i++) {
        int el = arr[i];
        Trie * next = cur->Find(el);
        if (!next) {
            next = new Trie(cur, el);
            cur->Insert(el, next);
            cur = next;
        } else {
            cur = next;
        }
    }
    return cur;
}

void ScanIntArray(int * arr, int len) {
    for (int i = 0; i < len; i++) cin >> arr[i];
}

void DFS(vector<int> & path, vector< vector<int> > & adj, int u) {
    for (int &v: adj[u]) {
        if (v == -1) continue;
        int tmp = v;
        v = -1;
        DFS(path, adj, tmp);
    }
    path.push_back(u);
}

vector<int> EulerPath(vector< vector<int> > & adj) {
    int n = adj.size();
    vector<int> in(n), out(n);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            in[j]++;
            out[i]++;
        }
    }
    vector<int> path;
    for (int i = 0; i < n; i++) if (in[i] < out[i]) {
        DFS(path, adj, i);
        return path;
    }
    for (int i = 0; i < n; i++) if (out[i]) {
        DFS(path, adj, i);
        return path;
    }
    return path;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k, pv = 0;
    Trie head(0, 0);
    Trie *tail;
    cin >> n >> m;
    k = n-m+1;
    vector< vector<int> > adj(k+2);
    vector< Trie* > tries(k+2);
    int * buf = new int[1010];
    for (int i = 0; i < k; i++) {
        int f, t;
        ScanIntArray(buf, m);

        tail = InsertSeq(&head, buf, m-1);
        if (tail->id == 0) {
            tail->id = ++pv;
            tries[tail->id] = tail;
        }
        f = tail->id;

        tail = InsertSeq(&head, buf+1, m-1);
        if (tail->id == 0) {
            tail->id = ++pv;
            tries[tail->id] = tail;
        }
        t = tail->id;

        adj[f].push_back(t);
    }

    vector<int> path = EulerPath(adj);
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int) path.size(); i++) {
        if (i == 0) {
            vector<int> record;
            Trie * cur = tries[path[0]];
            while (cur->parent) {
                record.push_back(cur->value);
                cur = cur->parent;
            }
            for (auto it = record.rbegin(); it != record.rend(); it++) {
                cout << (*it) << ' ';
            }
        } else {
            cout << tries[path[i]]->value << ' ';
        }
    } cout << '\n';
}
