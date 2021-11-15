struct Edge{
    int u, v;
    LL c;
};
LL max_flow(int n, const vector<Edge>& edges, int s, int t){
    vector<vector<int>> G(n), H(n * 2);
    vector<Edge> e;
    vector<int> h(n), cur(n), ch(n * 2);
    vector<LL> p(n);
    for(auto [u, v, c] : edges) if(u != v){
        G[u].push_back(e.size());
        e.push_back({u, v, c});
        G[v].push_back(e.size());
        e.push_back({v, u, 0});
    }
    auto push = [&](int i, LL f){
        if(not p[e[i].v] and f) H[h[e[i].v]].push_back(e[i].v);
        e[i].c -= f;
        e[i ^ 1].c += f;
        p[e[i].u] -= f;
        p[e[i].v] += f;
    };
    h[s] = n;
    ch[0] = n - 1;
    p[t] = 1;
    for(int i : G[s]) push(i, e[i].c);
    for(int hi = 0;;){
        while(H[hi].empty()) if(not hi --) return -p[s];
        int u = H[hi].back();
        H[hi].pop_back();
        while(p[u] > 0){
            if(cur[u] == (int)G[u].size()){
                h[u] = INT_MAX;
                for(int& i : G[u]) if(e[i].c and h[u] > h[e[i].v] + 1){
                    h[u] = h[e[i].v] + 1;
                    cur[u] = &i - G[u].data();
                }
                ch[h[u]] += 1;
                if(not(ch[hi] -= 1) and hi < n)
                    for(int i = 0; i < n; i += 1)
                        if(h[i] > hi and h[i] < n){
                            ch[h[i]] -= 1;
                            h[i] = n + 1;
                        }
                hi = h[u];
            }
            else{
                int i = G[u][cur[u]];
                if(e[i].c and h[u] == h[e[i].v] + 1) push(i, min(p[u], e[i].c));
                else cur[u] += 1;
            }
        }
    }
    return 0LL;
}