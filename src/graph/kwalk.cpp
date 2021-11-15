struct Edge{
    int u, v, w;
};
struct Node{
    int v, h;
    LL w;
    Node *ls, *rs;
    Node(int v, LL w) : v(v), w(w) {
        h = 1;
        ls = rs = nullptr;
    }
};
Node* merge(Node* u, Node* v) {
    if (u == nullptr) return v;
    if (v == nullptr) return u;
    if (u->w > v->w) swap(u, v);
    Node* p = new Node(*u);
    p->rs = merge(u->rs, v);
    if (p->rs != nullptr and (p->ls == nullptr or p->ls->h < p->rs->h)) swap(p->ls, p->rs);
    p->h = (p->rs ? p->rs->h : 0) + 1;
    return p;
}
vector<LL> k_shortest_walk(int N, const vector<Edge>& edges, int S, int T, int K) {
    vector<vector<int>> G(N);
    for (int i = 0; i < (int)edges.size(); i += 1) G[edges[i].v].push_back(i);
    priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> pq;
    vector<LL> d(N, -1);
    vector<int> done(N), par(N, -1), p;
    d[T] = 0;
    pq.push({0, T});
    while (not pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (done[u]) continue;
        p.push_back(u);
        done[u] = 1;
        for (int i : G[u]) {
            auto [v, _, w] = edges[i];
            if (d[v] == -1 or d[v] > d[u] + w) {
                d[v] = d[u] + w;
                par[v] = i;
                pq.push({d[v], v});
            }
        }
    }
    if (d[S] == -1) return vector<LL>(K, -1);
    vector<Node*> heap(N);
    for (int i = 0; i < (int)edges.size(); i += 1) {
        auto [u, v, w] = edges[i];
        if (~d[u] and ~d[v] and par[u] != i) heap[u] = merge(heap[u], new Node(v, d[v] + w - d[u]));
    }
    for (int u : p) if (u != T)
        heap[u] = merge(heap[u], heap[edges[par[u]].v]);
    priority_queue<pair<LL, Node*>, vector<pair<LL, Node*>>, greater<pair<LL, Node*>>> q;
    if (heap[S]) q.push({d[S] + heap[S]->w, heap[S]});
    vector<LL> res = {d[S]};
    for (int i = 1; i < K and not q.empty(); i += 1) {
        auto [w, node] = q.top();
        q.pop();
        res.push_back(w);
        if (heap[node->v]) q.push({w + heap[node->v]->w, heap[node->v]});
        for (auto s : {node->ls, node->rs})
            if (s) q.push({w + s->w - node->w, s});
    }
    res.resize(K, -1);
    return res;
}