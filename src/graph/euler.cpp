vector<int> undirected_circuit(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<int> vis(m), res;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; i += 1) {
        G[edges[i].first].push_back(i + 1);
        G[edges[i].second].push_back(-i - 1);
    }
    for (int i = 0; i < n; i += 1) if (G[i].size() & 1) return {};
    vector<vector<int>::const_iterator> it(n);
    for (int i = 0; i < n; i += 1) it[i] = G[i].begin();
    function<void(int)> dfs = [&](int u) {
        for (auto& nxt = it[u]; nxt != G[u].end(); ) {
            int i = abs(*nxt) - 1;
            if (not vis[i]) {
                vis[i] = 1;
                int w = *nxt;
                dfs(*nxt >= 0 ? edges[i].second : edges[i].first);
                res.push_back(-w);
            }
            else nxt = next(nxt);
        }
    };
    for (int i = 0; i < n; i += 1) if (not G[i].empty()) {
        dfs(i);
        break;
    }
    if (res.size() < m) return {};
    return res;
}

vector<int> directed_circuit(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<int> d(n), vis(m), res;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; i += 1) {
        G[edges[i].first].push_back(i);
        d[edges[i].second] += 1;
    }
    for (int i = 0; i < n; i += 1) if (G[i].size() != d[i]) return {};
    vector<vector<int>::const_iterator> it(n);
    for (int i = 0; i < n; i += 1) it[i] = G[i].begin();
    function<void(int)> dfs = [&](int u) {
        for (auto& nxt = it[u]; nxt != G[u].end(); ) {
            if (not vis[*nxt]) {
                vis[*nxt] = 1;
                int w = *nxt;
                dfs(edges[w].second);
                res.push_back(w);
            }
            else nxt = next(nxt);
        }
    };
    for (int i = 0; i < n; i += 1) if (not G[i].empty()) {
        dfs(i);
        break;
    }
    if (res.size() < m) return {};
    reverse(res.begin(), res.end());
    return res;
}