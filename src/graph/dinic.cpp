struct Edge{
    int u, v;
    LL c;
};
LL Dinic(int n, const vector<Edge>& edges, int s, int t){
    vector<vector<int>> G(n);
    vector<vector<int>::const_iterator> cur(n);
    vector<Edge> e;
    vector<int> d(n);
    for(int i = 0; i < (int)edges.size(); i += 1){
        G[edges[i].u].push_back(e.size());
        e.push_back(edges[i]);
        G[edges[i].v].push_back(e.size());
        e.push_back({edges[i].v, edges[i].u, 0});
    }
    auto bfs = [&](){
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while(not q.empty()){
            int u = q.front();
            q.pop();
            for(int i : G[u])
                if(e[i].c and d[e[i].v] == -1){
                    d[e[i].v] = d[u] + 1;
                    q.push(e[i].v);
                }
        }
        return d[t] != -1;
    };
    function<LL(int, LL)> dfs = [&](int u, LL f){
        if(u == t) return f;
        LL ret = 0;
        for(; cur[u] != G[u].end(); cur[u] = next(cur[u])){
            int i = *cur[u];
            if(d[e[i].v] != d[u] + 1 or not e[i].c) continue;
            LL pf = dfs(e[i].v, min(e[i].c, f));
            e[i].c -= pf;
            e[i ^ 1].c += pf;
            ret += pf;
            f -= pf;
            if(not f) break;
        }
        return ret;
    };
    LL ret = 0;
    while(bfs()){
        for(int i = 0; i < n; i += 1) cur[i] = G[i].begin();
        ret += dfs(s, LLONG_MAX);
    }
    return ret;
}