#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

int n;
int costs[16][16];
bool queued[1 << 16];
int min_cost[1 << 16];

vector< pair<int, int> > next_states(int current_state, int current_cost) {
    vector< pair<int, int> > states;
    for (int i = 0; i < n; i++) {
        if (current_state & (1 << i))
            continue;
        
        int addi_cost = inf;
        for (int j = 0; j < n; j++) {
            if (current_state & (1 << j)) {
                addi_cost = min(addi_cost, costs[j][i]);
            }
        }

        const int next_state = current_state | (1 << i);
        states.push_back(make_pair(next_state, current_cost + addi_cost));
    }
    return states;
}

int count_on(int state) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (state & (1 << i))
            ++count;
    }
    return count;
}

int read_init_state() {
    string str_init_state;
    cin >> str_init_state;
    int init_state = 0;
    for (int i = 0; i < str_init_state.length(); i++) {
        if (str_init_state[i] == 'Y')
            init_state |= 1 << i;
    }
    return init_state;
}

int read_int() {
    int x; cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> costs[i][j];
        }
    }

    const int init_state = read_init_state();
    const int p = read_int();

    memset(min_cost, 0x3f, sizeof(min_cost));

    queue<int> q;
    q.push(init_state);
    min_cost[init_state] = 0;
    int answer = inf;
    while (!q.empty()) {
        const int state = q.front();
        q.pop();
        if (count_on(state) >= p) {
            answer = min(answer, min_cost[state]);
            continue;
        }
        for (auto next: next_states(state, min_cost[state])) {
            const int next_state = next.first;
            const int next_cost = next.second;
            min_cost[next_state] = min(min_cost[next_state], next_cost);
            if (!queued[next_state]) {
                queued[next_state] = true;
                q.push(next_state);
            }
        }
    }

    cout << (answer >= inf ? -1 : answer);

    return 0;
}
