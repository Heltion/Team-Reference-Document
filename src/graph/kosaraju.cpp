vector<int> kosaraju(const vector<vector<int>>& G){
    int n = G.size(), c = 0;
    vector<int> vis(n), res(n, -1), p;
    vector<vector<int>> H(n);
    function<void(int)> DFS1 = [&](int u){
        vis[u] = 1;
        for(int v : G[u]) if(not vis[v]) DFS1(v);
        p.push_back(u);
    };
    function<void(int)> DFS2 = [&](int u){
        res[u] = c;
        for(int v : H[u]) if(not ~res[v]) DFS2(v);
    };
    for(int i = 0; i < n; i += 1) for(int j : G[i]) H[j].push_back(i);
    for(int i = 0; i < n; i += 1) if(not vis[i]) DFS1(i);
    reverse(p.begin(), p.end());
    for(int i : p) if(not ~res[i]) DFS2(i), c += 1;
    return res;
}