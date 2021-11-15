vector<int> directed_euler_circuit(int n, int m, const vector<vector<pair<int, int> > >& G){
    vector<int> d(n);
    for(const auto& A : G) for(auto p : A) d[p.first] += 1;
    for(int i = 0; i < n; i += 1) if(G[i].size() != d[i]) return {};
    vector<vector<pair<int, int> >::const_iterator> it(n);
    for(int i = 0; i < n; i += 1) it[i] = G[i].begin();
    vector<int> vis(m + 1), p;
    function<void(int)> dfs = [&](int u){
        for(auto& nxt = it[u]; nxt != G[u].end();)
            if(not vis[nxt->second]){
                vis[nxt->second] = 1;
                int v = nxt->second;
                dfs(nxt->first);
                p.push_back(v);
            }
            else nxt = next(nxt);
    };
    for(int i = 0; i < n; i += 1) if(not G[i].empty()){
        dfs(i);
        break;
    }
    if(p.size() < m) return {};
    reverse(p.begin(), p.end());
    return p;
}

vector<int> undirected_euler_circuit(int n, int m, const vector<vector<pair<int, int> > >& G){
    for(const auto& A : G) if(A.size() & 1) return {};
    vector<vector<pair<int, int> >::const_iterator> it(n);
    for(int i = 0; i < n; i += 1) it[i] = G[i].begin();
    vector<int> vis(m + 1), p;
    function<void(int)> dfs = [&](int u){
        for(auto& nxt = it[u]; nxt != G[u].end();)
            if(not vis[abs(nxt->second)]){
                vis[abs(nxt->second)] = 1;
                int v = nxt->second;
                dfs(nxt->first);
                p.push_back(v);
            }
            else nxt = next(nxt);
    };
    for(int i = 0; i < n; i += 1) if(not G[i].empty()){
        dfs(i);
        break;
    }
    if(p.size() < m) return {};
    reverse(p.begin(), p.end());
    return p;
}