vector<int> dominator_tree(const vector<vector<int>>& G, int r){
    int n = G.size(), ts = 0;
    vector<int> dfn(n, -1), par(n), ord(n), f(n), mn(n), sdom(n), dom(n);
    vector<vector<int>> H(n), I(n);
    for(int i = 0; i < n; i += 1){
        for(int j : G[i]) H[j].push_back(i);
        f[i] = sdom[i] = mn[i] = i;
    }
    function<void(int)> dfs = [&](int u){
        ord[dfn[u] = ts ++] = u;
        for(int v : G[u]) if(not ~dfn[v]){
            par[v] = u;
            dfs(v);
        }
    };
    function<int(int)> find = [&](int u){
        if(u == f[u]) return u;
        int fu = find(f[u]);
        if(dfn[sdom[mn[f[u]]]] < dfn[sdom[mn[u]]]) mn[u] = mn[f[u]];
        return f[u] = fu; 
    };
    dfs(r);
    for(int i = n - 1; i; i -= 1){
        int u = ord[i];
        for(int v : H[u]) if(~dfn[v]){
            find(v);
            if(dfn[sdom[mn[v]]] < dfn[sdom[u]]) sdom[u] = sdom[mn[v]];
        }
        I[sdom[u]].push_back(u);
        u = f[u] = par[u];
        for(int v : I[u]){
            find(v);
            dom[v] = u == sdom[mn[v]] ? u : mn[v];
        }
        I[u].clear();
    }
    for(int u : ord) if(dom[u] != sdom[u]) dom[u] = dom[dom[u]];
    return dom;
}