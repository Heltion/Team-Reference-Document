struct Edge{
    int u, v;
    LL cost, cap, flow;
};
pair<LL, LL> successive_shortest_path(int n, const vector<Edge>& E, int s, int t){
    vector<vector<int>> G(n);
    vector<Edge> edges;
    vector<LL> h(n), d(n);
    vector<int> p(n), done(n);
    vector<vector<int>::iterator> nxt(n);
    for(auto e : E){
        G[e.u].push_back(edges.size());
        edges.push_back(e);
        G[e.v].push_back(edges.size());
        edges.push_back({e.v, e.u, -e.cost, 0, 0});
    }
    auto dijkstra = [&](){
        fill(d.begin(), d.end(), 1E18);
        fill(p.begin(), p.end(), -1);
        fill(done.begin(), done.end(), 0);
        priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> q;
        q.push({d[s] = 0, s});
        while(not q.empty()){
            int u = q.top().second;
            q.pop();
            if(done[u]) continue;
            done[u] = 1;
            for(int i : G[u])
                if(edges[i].cap > edges[i].flow and d[edges[i].v] > d[u] + h[u] + edges[i].cost - h[edges[i].v]){
                    p[edges[i].v] = i;
                    q.push({d[edges[i].v] = d[u] + h[u] + edges[i].cost - h[edges[i].v], edges[i].v});
                }
        }
        return ~p[t];
    };
    LL f = 0, c = 0;
    while(dijkstra()){
        for(int i = 0; i < n; i += 1) h[i] += d[i];
        LL nf = LLONG_MAX;
        for(int u = t; u != s; u = edges[p[u]].u) nf = min(nf, edges[p[u]].cap - edges[p[u]].flow);
        f += nf;
        c += h[t] * nf;
        for(int u = t; u != s; u = edges[p[u]].u){
            edges[p[u]].flow += nf;
            edges[p[u] ^ 1].flow -= nf;
        }
    }
    return {f, c};
}