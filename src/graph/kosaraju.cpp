vector<vector<int>> kosaraju(int n, const vector<pair<int, int>>& edges){
    vector<int> vis(n), p;
    vector<vector<int>> res, G(n), Gt(n);
    for (auto [a, b] : edges) {
        G[a].push_back(b);
        Gt[b].push_back(a);
    }
    function<void(int)> dfs = [&](int u){
        vis[u] = 1;
        for(int v : G[u]) if(not vis[v]) dfs(v);
        p.push_back(u);
    };
    function<void(int)> dfst = [&](int u){
        vis[u] = 0;
        res.back().push_back(u);
        for(int v : Gt[u]) if(vis[v]) dfst(v);
    };
    for(int i = 0; i < n; i += 1) if(not vis[i]) dfs(i);
    reverse(p.begin(), p.end());
    for(int i : p) if(vis[i]) {
        res.emplace_back();
        dfst(i);
    }
    return res;
}