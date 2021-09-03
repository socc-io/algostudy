#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solver {
public:
    vector<int> p, q;
    vector<bool> visit;
    vector<int> track;
    Solver(vector<int> p, vector<int> q): p(p), q(q), visit(p.size(), false) {}  

    bool findcomb(int target, int index, int index2) {
        if (target == 0) {
            if (index2 == q.size() - 1) return true;
            for (int i: track) visit[i] = true;
            vector<int> t_track(track.begin(), track.end());
            track.clear();
            if (findcomb(q[index2+1], 0, index2+1)) return true;
            for (int i: t_track) visit[i] = false;
            track.clear(); 
            copy(t_track.begin(), t_track.end(), back_inserter(track));
            return false;
        }

        if (index >= p.size()) return false;
        if (p[index] > target) return false;
        if (visit[index]) return findcomb(target, index + 1, index2);

        track.push_back(index);
        if (findcomb(target - p[index], index + 1, index2)) return true;
        track.pop_back();

        if (findcomb(target, index + 1, index2)) return true;

        return false;
    }
};

bool solve(const vector<int> & vp, const vector<int> & vq) {
    vector<int> np, nq;
    multiset<int> q(vq.begin(), vq.end());

    for (int v: vp) {
        auto it = q.find(v);
        if (it != q.end()) q.erase(it);
        else np.push_back(v);
    }
    sort(np.begin(), np.end());
    for (int v: q) nq.push_back(v);

    if (nq.size() == 0) return true;

    Solver solver(np, nq);
    return solver.findcomb(nq[0], 0, 0);
}

vector<bool> solution(vector<vector<int>> p, vector<vector<int>> q) {
    vector<bool> answer;
    for (int i = 0; i < p.size(); i++) {
        answer.push_back(solve(p[i], q[i]));
    }
    return answer;
}

int main() {
    cout << solve({4, 3, 3}, {5, 5});
    return 0;
}
