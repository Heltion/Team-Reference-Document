bool miller_rabin(LL n){
    static LL p[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    if(n == 1) return false;
    if(n == 2) return true;
    if(not(n & 1)) return false;
    LL d = n - 1, r = 0;
    for(; not(d & 1); d >>= 1) r += 1;
    bool res = true;
    for(int i = 0; i < 9 and p[i] < n and res; i += 1){
        LL x = power(p[i], d, n);
        if(x == 1 or x == n - 1) continue;
        for(int j = 1; j < r; j += 1){
            x = mul(x, x, n);
            if(x == n - 1) break;
        }
        if(x != n - 1) res = false;
    }
    return res;
};