#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
vector<int> adj[100005];
bool visited[100005];

// DFS to count the size of a component, avoiding node 'avoid'
int dfs(int u, int avoid) {
    visited[u] = true;
    int count = 1;
    for (int v : adj[u]) {
        if (v == avoid || visited[v]) continue;
        count += dfs(v, avoid);
    }
    return count;
}

// Check if removing node 'u' satisfies the condition
bool check(int u) {
    // Reset visited array
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }
    visited[u] = true; // Mark u as visited so it's effectively removed

    // Check each neighbor of u (these will be roots of separate components)
    for (int v : adj[u]) {
        if (visited[v]) continue;
        int componentSize = dfs(v, u);
        if (componentSize > k) {
            return false;
        }
    }

    // Also need to check all other unvisited nodes (in case there are disconnected parts)
    for (int i = 1; i <= n; i++) {
        if (i != u && !visited[i]) {
            int componentSize = dfs(i, u);
            if (componentSize > k) {
                return false;
            }
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
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }

    return 0;
}
