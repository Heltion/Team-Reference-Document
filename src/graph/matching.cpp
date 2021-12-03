vector<int> matching(int n, const vector<pair<int, int>>& edges) {
    int time = 0;
    vector<int> matched(n, -1), pre(n, -1), vis(n);
    vector<vector<int>> G(n);
    for (auto [x, y] : edges) {
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 0; i < n; i += 1)
        if (matched[i] == -1)
            [&](int s) {
                vector<int> p(n), type(n, -1);
                for (int i = 0; i < n; i += 1) p[i] = i;
                function<int(int)> fp = [&](int u) {
                    return u == p[u] ? u : p[u] = fp(p[u]);
                };
                queue<int> q;
                auto push = [&](int u) {
                    q.push(u);
                    type[u] = 0;
                };
                push(s);
                while (not q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : G[u])
                        if (type[v] == -1) {
                            pre[v] = u, type[v] = 1;
                            if (matched[v] == -1) {
                                for (int x = u, y = v, tmp; x != -1; x = pre[y]) {
                                    tmp = matched[x], matched[x] = y, matched[y] = x;
                                    if ((y = tmp) == -1) break;
                                }
                                return;
                            }
                            push(matched[v]);
                        }
                        else if (not type[v] and fp(u) != fp(v)) {
                            int w = [&](int u, int v) {
                                for (time += 1, u = fp(u), v = fp(v); ; swap(u, v))
                                    if (~u) {
                                        if (vis[u] == time) return u;
                                        vis[u] = time;
                                        if (matched[u] == -1 or pre[matched[u]] == -1)
                                            u = -1;
                                        else u = fp(pre[matched[u]]);
                                    }
                            }(u, v);
                            auto blossom = [&](int u, int v, int w) {
                                while (fp(u) != w) {
                                    pre[u] = v;
                                    v = matched[u];
                                    if (type[matched[u]] == 1) push(matched[u]);
                                    if (p[u] == u) p[u] = w;
                                    if (p[v] == v) p[v] = w;
                                    u = pre[v];
                                }
                            };
                            blossom(u, v, w);
                            blossom(v, u, w);
                        }
                }
            }(i);
    return matched;
}