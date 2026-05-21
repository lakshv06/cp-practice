#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1, arr);
    }

    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, arr);
            build(2 * node + 2, mid + 1, end, arr);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        propagate(node, start, end);
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            lazy[node] += val;
            propagate(node, start, end); // Apply immediately to ensure parent sums are correct
            return;
        }
        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, val);
        updateRange(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // Now safe as children propagated
    }

    void update(int l, int r, int val) {
        updateRange(0, 0, n - 1, l, r, val);
    }

    int queryRange(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (start > r || end < l) return 0;
        if (start >= l && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return queryRange(2 * node + 1, start, mid, l, r) +
               queryRange(2 * node + 2, mid + 1, end, l, r);
    }

    int query(int l, int r) {
        return queryRange(0, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    segTree.update(1, 3, 5);

    cout << "Sum of elements from 1 to 3: " << segTree.query(1, 3) << endl;
    cout << "Sum of entire array: " << segTree.query(0, 5) << endl;

    return 0;
}