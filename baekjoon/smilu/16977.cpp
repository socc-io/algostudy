#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;

struct Rectangle {
    int height;
} rects[MAX_N];
int num_rects;

struct Height {
    int value;
    int index;

    bool operator < (const Height &h) const {
        return value > h.value;
    }
} heights[MAX_N];

struct Range {
    int left;
    int right;

    int Mid() const {
        return (left + right) >> 1;
    }

    int Length() const {
        return right - left;
    }

    Range HalfLeft() const {
        return Range { left, Mid() };
    }

    Range HalfRight() const {
        return Range{ Mid(), right };
    }

    bool Including(Range r) const {
        return left <= r.left && r.right <= right;
    }

    bool Exclusive(Range r) const {
        return r.right <= left || r.left >= right;
    }

    bool Including(int index) const {
        return left <= index && index < right;
    }

};

// Persistent Segment Tree
struct PSTree {
    struct Node {
        int LMS;
        int RMS;
        int MS;

        Range range;
        const Node *left;
        const Node *right;

        int Length() const {
            return range.Length();
        }

        static Node Merge(const Node &a, const Node &b) {
            const int R_LMS = a.LMS + b.LMS * (a.LMS == a.Length());
            const int R_RMS = b.RMS + a.RMS * (b.RMS == b.Length());
            const int R_MS = max({ a.MS, b.MS, R_LMS, R_RMS, a.RMS + b.LMS });
            return Node { R_LMS, R_RMS, R_MS, Range { a.range.left, b.range.right }, &a, &b };
        }

    } node_pool[20 * MAX_N];

    int next_node = 0;
    Node& GetNode() {
        return node_pool[next_node++];
    }

    Node& GetNode(int v, Range range) {
        Node& n = GetNode();
        return n = { v, v, v, range, &n, &n };
    }

    Node& Merge(const Node &a, const Node &b) {
        return GetNode() = Node::Merge(a, b);
    }

    Node& Build(Range range, int min_height) {
        if (range.Length() == 1) {
            const int height = rects[range.left].height;
            return GetNode(height >= min_height, range);
        } else {
            const Node& left = Build(range.HalfLeft(), min_height);
            const Node& right = Build(range.HalfRight(), min_height);
            return Merge(left, right);
        }
    }

    Node& Set(const Node& root, int target) {
        if (root.Length() == 1) {
            return GetNode(1, root.range);
        }
        if (target < root.range.Mid()) {
            return Merge(Set(*root.left, target), *root.right);
        } else {
            return Merge(*root.left, Set(*root.right, target));
        }
    }

    const Node Query(const Node& root, Range query) {
        if (root.MS == 0) {
            return Node { 0, 0, 0, root.range, nullptr, nullptr };
        }
        if (query.Including(root.range)) {
            return root;
        }
        if (query.Exclusive(root.range)) {
            return Node { 0, 0, 0, root.range, nullptr, nullptr };
        }
        const Node left_result = Query(*root.left, query);
        const Node right_result = Query(*root.right, query);
        return Node::Merge(left_result, right_result);
    }
    
} tree;

PSTree::Node roots[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> num_rects;
    for (int i = 0; i < num_rects; i++) {
        cin >> rects[i].height;
        heights[i].value = rects[i].height;
        heights[i].index = i;
    }

    sort(heights, heights + num_rects);

    roots[0] = tree.Build({ 0, num_rects }, heights[0].value);
    for (int i = 1; i < num_rects; i++) {
        roots[i] = tree.Set(roots[i-1], heights[i].index);
    }

    int left_queries;
    cin >> left_queries;
    while (left_queries--) {
        int l, r, w;
        cin >> l >> r >> w;
        const Range query { l - 1, r };

        // Binary search
        Range range { 0, num_rects };
        while (range.Length() > 1) {
            const PSTree::Node result = tree.Query(roots[range.Mid()], query);
            const int max_w = result.MS;
            if (max_w >= w) {
                range = range.HalfLeft();
            } else {
                range = range.HalfRight();
            }
        }
    
        int ans = heights[range.right].value;
        if (range.left == 0) {
            if (tree.Query(roots[0], query).MS >= w) {
                ans = heights[0].value;
            }
        }
        
        cout << ans << '\n';
    }

    return 0;
}
