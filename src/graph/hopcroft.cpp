vector<int> max_matching(int m, const vector<vector<int>>& G){
    int n = G.size();
    vector<int> A(n), B(m), res(m, -1), cur, next;
    while(true){
        fill(A.begin(), A.end(), 0);
        fill(B.begin(), B.end(), -1);
        cur.clear();
        for(int i : res) if(i != -1) A[i] = -1;
        for(int i = 0; i < n; i += 1) if(not A[i]) cur.push_back(i);
        for(int L = 1;; L += 2){
            bool isLast = false;
            next.clear();
            for(int i : cur) for(int j : G[i]){
                if(res[j] == -1){
                    B[j] = L;
                    isLast = true;
                }
                else if(res[j] != i and B[j] == -1){
                    B[j] = L;
                    next.push_back(res[j]);
                }
            }
            if(isLast) break;
            if(next.empty()) return res;
            for(int i : next) A[i] = L + 1;
            cur.swap(next);
        }
        function<bool(int, int)> dfs = [&](int u, int L){
            if(A[u] != L) return false;
            A[u] = -1;
            for(int v : G[u]) if(B[v] == L + 1){
                B[v] = -1;
                if(res[v] == -1 or dfs(res[v], L + 2))
                    return res[v] = u, true;
            }
            return false;
        };
        for(int i = 0; i < n; i += 1)
            dfs(i, 0);
    }
    return res;
}