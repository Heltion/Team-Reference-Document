vector<int> km(const vector<vector<LL>>& w) {
    int n = w.size();
    vector<LL> hl(n), hr(n);
    vector<int> fl(n, -1), fr(n, -1), pre(n);
    for (int i = 0; i < n; i += 1) hl[i] = *max_element(w[i].begin(), w[i].end());
    for (int s = 0; s < n; s += 1)
        [&](int s){
            vector<LL> slack(n, inf);
            vector<int> vl(n), vr(n);
            queue<int> q;
            q.push(s);
            vr[s] = 1;
            auto check = [&](int u) {
                vl[u] = 1;
                if (fl[u] != -1) {
                    q.push(fl[u]);
                    vr[fl[u]] = 1;
                    return 1;
                }
                while (u != -1) swap(u, fr[fl[u] = pre[u]]);
                return 0;
            };
            while (true) {
                while (not q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int i = 0; i < n; i += 1) {
                        LL d = hl[i] + hr[u] - w[i][u];
                        if (not vl[i] and slack[i] >= d) {
                            pre[i] = u;
                            if (d) slack[i] = d;
                            else if (not check(i)) return;
                        }
                    }
                }
                LL d = inf;
                for (int i = 0; i < n; i += 1)
                    if (not vl[i]) d = min(d, slack[i]);
                for (int i = 0; i < n; i += 1)
                    if (vl[i]) hl[i] += d;
                    else slack[i] -= d;
                for (int i = 0; i < n; i += 1) if (vr[i]) hr[i] -= d;
                for (int i = 0; i < n; i += 1)
                    if (not vl[i] and not slack[i] and not check(i))
                        return;
            }
        }(s);
    return fl;
}