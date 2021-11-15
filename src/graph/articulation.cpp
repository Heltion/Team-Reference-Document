vector<int> articulation_points(int n, const vector<vector<int>>& G){
    int ts = 0;
    vector<int> dfn(n), low(n), cut(n);
    function<void(int, int)> dfs = [&](int u, int p){
        dfn[u] = low[u] = ts ++;
        int c = 0;
        for(int v : G[u])
            if(not ~dfn[v]){
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u] and ~p) cut[u] = 1;
                c += 1;
            }
            else low[u] = min(low[u], dfn[v]);
        if(not ~p and c > 1) cut[u] = 1;
    };
    for(int i = 0; i < n; i += 1) if(not dfn[i]) dfs(i, -1);
    vector<int> res;
    for(int i = 0; i < n; i += 1) if(cut[i]) res.push_back(i);
    return res;
}