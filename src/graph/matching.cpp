vector<pair<int, int>> matching(int n, const vector<pair<int, int>>& vp){
    vector<vector<LL>> mat(n, vector<LL>(n)), A;
    mt19937 rand(0);
    for(auto [u, v] : vp){
        LL r = rand() % mod;
        mat[u][v] = r;
        mat[v][u] = (mod - r) % mod;
    }
    int r = matrix_inverse(A = mat), m = 2 * n - r, fi = 0, fj = 0;
    assert(r % 2 == 0);
    if(m != n) do{
        mat.resize(m, vector<LL>(m));
        for(int i = 0; i < n; i += 1){
            mat[i].resize(m);
            for(int j = n; j < m; j += 1){
                LL r = rand() % mod;
                mat[i][j] = r;
                mat[j][i] = (mod - r) % mod;
            }
        }
    }while(matrix_inverse(A = mat) != m);
    vector<int> has(m, 1);
    vector<pair<int, int>> res;
    auto rem = [&](int fi, int fj){
        LL a = power(A[fi][fj], mod - 2);
        for(int i = 0; i < m; i += 1) if(has[i] and A[i][fj]){
            LL b = A[i][fj] * a % mod;
            for(int j = 0; j < m; j += 1) A[i][j] = (A[i][j] + mod -  A[fi][j] * b % mod) % mod;
        }
    };
    for(int _ = 0; _ < m / 2; _ += 1){
        int done = 0;
        for(int i = 0; i < m and not done; i += 1) if(has[i])
            for(int j = i + 1; j < m; j += 1) if(A[i][j] and mat[i][j]){
                fi = i;
                fj = j;
                done = 1;
                break;
            }
        if(fj < n) res.push_back({fi, fj});
        has[fi] = has[fj] = 0;
        rem(fi, fj);
        rem(fj, fi);
    }
    return res;
}