#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    // Constructor initializes the segment tree and lazy array
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);  // Segment tree size
        lazy.resize(4 * n, 0);  // Lazy propagation array
        build(0, 0, n - 1, arr); // Build the segment tree
    }

    // Build function to initialize the segment tree from the array
    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            // Leaf node stores the value of the array element
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            // Recursively build the left and right subtrees
            build(2 * node + 1, start, mid, arr);        // Left child
            build(2 * node + 2, mid + 1, end, arr);      // Right child
            // Internal node stores the sum of the left and right child nodes
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    // Function to propagate the lazy updates to children
    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) { // If there is a pending update
            // Apply the pending update to the current node
            tree[node] += (end - start + 1) * lazy[node]; // Update the current node value
            // If not a leaf node, propagate the update to the children
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];  // Left child update
                lazy[2 * node + 2] += lazy[node];  // Right child update
            }
            // Clear the lazy value for the current node
            lazy[node] = 0;
        }
    }

    // Range update function with lazy propagation
    void updateRange(int node, int start, int end, int l, int r, int val) {
        propagate(node, start, end); // Apply any pending updates to the current node

        // No overlap
        if (start > r || end < l) return;

        // Complete overlap: mark the lazy update and defer propagation
        if (start >= l && end <= r) {
            lazy[node] += val;  // Mark the update in the lazy array
            return; // Do not propagate immediately, defer to next operation
        }

        // Partial overlap: recurse on the children without direct propagation
        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, val);  // Left child
        updateRange(2 * node + 2, mid + 1, end, l, r, val);  // Right child

        // Update the current node's value based on its children after processing
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Public function to initiate range update
    void update(int l, int r, int val) {
        updateRange(0, 0, n - 1, l, r, val);
    }

    // Query function with lazy propagation to ensure lazy updates are applied when needed
    int queryRange(int node, int start, int end, int l, int r) {
        propagate(node, start, end); // Apply any pending updates to the current node

        // No overlap
        if (start > r || end < l) return 0;

        // Complete overlap
        if (start >= l && end <= r) return tree[node];

        // Partial overlap: query both children
        int mid = (start + end) / 2;
        int leftSum = queryRange(2 * node + 1, start, mid, l, r);  // Left child
        int rightSum = queryRange(2 * node + 2, mid + 1, end, l, r);  // Right child
        return leftSum + rightSum;
    }

    // Public function to initiate range query
    int query(int l, int r) {
        return queryRange(0, 0, n - 1, l, r);
    }
};

int main() {
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    vector<int> arr = {1, 3, 5, 7, 9, 11}; // Initial array
    SegmentTree segTree(arr);

    // Range update: add 5 to all elements from index 1 to 3
    segTree.update(1, 3, 5);

    // Range query: sum of elements from index 1 to 3
    cout << "Sum of elements from 1 to 3: " << segTree.query(1, 3) << endl;

    // Additional updates and queries can be added here for further testing
    return 0;
}
