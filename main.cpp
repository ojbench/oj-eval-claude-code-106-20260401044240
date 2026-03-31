#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> adj[100005];
int subtree_size[100005];
int parent[100005];
bool valid[100005];

// DFS to compute subtree sizes with 'root' as the root of the tree
void compute_subtree_sizes(int u, int p) {
    parent[u] = p;
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        compute_subtree_sizes(v, u);
        subtree_size[u] += subtree_size[v];
    }
}

// Check if removing node 'u' satisfies the condition
bool check(int u) {
    // When we remove node u, it splits into multiple components:
    // 1. Each child's subtree (in the rooted tree)
    // 2. The parent side (everything else)

    // Check all children's subtrees
    for (int v : adj[u]) {
        if (v == parent[u]) continue; // Skip parent
        if (subtree_size[v] > k) {
            return false;
        }
    }

    // Check the parent side (if u is not the root)
    if (parent[u] != -1) {
        // Size of parent side = total nodes - u's subtree
        int parent_side_size = n - subtree_size[u];
        if (parent_side_size > k) {
            return false;
        }
    }

    return true;
}

int main() {
    cin >> n >> k;

    // Read edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Compute subtree sizes with node 1 as root
    compute_subtree_sizes(1, -1);

    // Find all valid nodes
    vector<int> result;
    for (int u = 1; u <= n; u++) {
        if (check(u)) {
            result.push_back(u);
        }
    }

    // Sort in descending order
    sort(result.begin(), result.end(), greater<int>());

    // Output result
    if (result.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }

    return 0;
}
