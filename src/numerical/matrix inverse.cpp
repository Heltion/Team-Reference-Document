int matrix_inverse(vector<vector<LL>>& A){
    int n = A.size(), rank = 0;
    vector<vector<LL>> B(n, vector<LL>(n));
    for(int i = 0; i < n; i += 1) B[i][i] = 1;
    for(int i = 0, r = 0; i < n; i += 1){
        int k = -1;
        for(int j = r; j < n; j += 1) if(A[j][i]){
            k = j;
            break;
        }
        if(k == -1) continue;
        swap(A[r], A[k]);
        swap(B[r], B[k]);
        LL inv = power(A[r][i], mod - 2);
        for(int j = i; j < n; j += 1) A[r][j] = A[r][j] * inv % mod;
        for(int j = 0; j < n; j += 1) B[r][j] = B[r][j] * inv % mod;
        for(int j = 0; j < n; j += 1) if(j != r){
            LL c = A[j][i];
            for(int k = i; k < n; k += 1) A[j][k] = (A[j][k] + mod - A[r][k] * c % mod) % mod;
            for(int k = 0; k < n; k += 1) B[j][k] = (B[j][k] + mod - B[r][k] * c % mod) % mod;
        }
        rank += 1;
        r += 1;
    }
    for(int i = 0; i < n; i += 1)
        for(int j = 0; j < n; j += 1)
            A[i][j] = B[i][j];
    return rank;
}