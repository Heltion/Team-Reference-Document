struct Edge{
    int u, v, w;
};
struct node{
    Edge key;
    node *L, *R;
    LL delta;
    node(Edge key) : key(key){
        L = R = nullptr;
        delta = 0;
    }
    void down(){
        key.w += delta;
        if(L) L->delta += delta;
        if(R) R->delta += delta;
        delta = 0;
    }
    Edge top(){
        down();
        return key;
    }
};
node* merge(node* u, node* v){
    if(not u or not v) return u ?: v;
    u->down(); v->down();
    if(u->key.w > v->key.w) swap(u, v);
    swap(u->L, (u->R = merge(v, u->R)));
    return u;
}
void pop(node*& u){
    u->down();
    u = merge(u->L, u->R);
}
struct union_find : vector<int>{
    vector<pair<int, int>> st;
    union_find(int n) : vector<int>(n, -1){}
    int time(){return st.size();}
    int find(int u){return at(u) < 0 ? u : find(at(u));}
    void roll_back(int t){
        for(int i = time() - 1; i >= t; i -= 1)
            at(st[i].first) = st[i].second;
        st.resize(t);
    }
    int unite(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return 0;
        if(at(u) > at(v)) std::swap(u, v);
        st.push_back({u, at(u)});
        st.push_back({v, at(v)});
        at(v) += at(u);
        at(u) = v;
        return 1;
    }
};
pair<LL, vector<int>> dmst(int n, const vector<Edge>& edges, int r){
    union_find uf(n);
    vector<node*> heap(n);
    for(Edge e : edges) heap[e.v] = merge(heap[e.v], new node(e));
    LL res = 0;
    vector<int> vis(n, -1), path(n), p(n);
    p[r] = vis[r] = r;
    vector<Edge> q(n), in(n, {-1, -1, 0});
    deque<tuple<int, int, vector<Edge>>> cycs;
    for(int i = 0; i < n; i += 1){
        int u = i, v = 0, qi = 0;
        while(vis[u] == -1){
            if(not heap[u]) return {-1, {}};
            Edge e = heap[u]->top();
            heap[u]->delta -= e.w;
            pop(heap[u]);
            q[qi] = e;
            path[qi ++] = u;
            vis[u] = i;
            res += e.w;
            u = uf.find(e.u);
            if(vis[u] == i){
                node* cyc = nullptr;
                int end = qi, time = uf.time();
                do cyc = merge(cyc, heap[v = path[qi -= 1]]);
                while(uf.unite(u, v));
                u = uf.find(u);
                heap[u] = cyc;
                vis[u] = -1;
                cycs.push_front({u, time, {&q[qi], &q[end]}});
            }
        }
        for(int i = 0; i < qi; i += 1) in[uf.find(q[i].v)] = q[i];
    }
    for(auto& [u, t, comp] : cycs){
        uf.roll_back(t);
        Edge in_edge = in[u];
        for(auto& e : comp) in[uf.find(e.v)] = e;
        in[uf.find(in_edge.v)] = in_edge;
    }
    for(int i = 0; i < n; i += 1) if(i != r) p[i] = in[i].u;
    return {res, p};
}