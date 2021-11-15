struct Edge{
    int u, v;
    LL c, w;
};
pair<LL, LL> min_cost_max_flow(int n, vector<Edge>& edges, int s, int t){
    static constexpr LL inf = 1E12;
    static constexpr int w = 40;
    vector<vector<int>> G(n);
    vector<Edge> e;
    vector<int> done(n), pre(n);
    vector<LL> dis(n), h(n);
    edges.push_back({t, s, inf, -inf});
    for(auto [u, v, c, w] : edges){
        G[u].push_back(e.size());
        e.push_back({u, v, 0, w});
        G[v].push_back(e.size());
        e.push_back({v, u, 0, -w});
    }
    auto hw = [&](int i){
        return e[i].w + h[e[i].u] - h[e[i].v];
    };
    auto dijkstra = [&](int s){
        priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> q; 
        fill(done.begin(), done.end(), 0);
        fill(dis.begin(), dis.end(), -1);
        fill(pre.begin(), pre.end(), -1);
        if(s != n) q.push({dis[s] = 0, s});
        else for(int i = 0; i < n; i += 1) q.push({dis[i] = -h[i], i});
        while(not q.empty()){
            int u = q.top().second;
            q.pop();
            if(done[u]) continue;
            done[u] = 1;
            for(int i : G[u])
                if(e[i].c and (dis[e[i].v] == -1 or dis[e[i].v] > dis[u] + hw(i))){
                    pre[e[i].v] = i;
                    q.push({dis[e[i].v] = dis[u] + hw(i), e[i].v});
                }
        }
    };
    auto add_cap = [&](int i){
        if(e[i].c){
            e[i].c += 1;
            return;
        }
        int u = e[i].u, v = e[i].v;
        dijkstra(v);
        if(dis[u] != -1 and dis[u] + hw(i) < 0){
            e[i ^ 1].c += 1;
            while(u != v){
                int j = pre[u];
                e[j].c -= 1;
                e[j ^ 1].c += 1;
                u = e[j].u;
            }
        }
        else e[i].c += 1;
        LL max_dis = 0, cur = hw(i);
        for(int j = 0; j < n; j += 1) if(dis[j] != -1) max_dis = max(max_dis, dis[i]);
        for(int j = 0; j < n; j += 1)
            if(dis[j] == -1)
                h[j] += max_dis + max(0LL, -cur);
            else h[j] += dis[j];
        dijkstra(n);
        for(int j = 0; j < n; j += 1) h[j] += dis[j];
    };
    for(int i = w; i >= 0; i -= 1){
        for(auto& [u, v, c, w] : e) c <<= 1;
        for(int j = 0; j < (int)edges.size(); j += 1)
            if((edges[j].c >> i) & 1)
                add_cap(j << 1);
    }
    edges.pop_back();
    LL c = 0;
    for(int i = 0; i < (int)edges.size(); i += 1)
        c += e[i << 1 | 1].c * e[i << 1].w;
    return {e.back().c, c};
}