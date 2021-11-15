LL log(LL a, LL b, LL p){
    LL res = 0, k = 1, d;
    if(b == 1) return 0;
    if(not a) return b ? -1 : 1;
    for(;k != b and (d = gcd(a, p)) != 1; res += 1){
        if(b % d) return -1;
        p /= d;
        b /= d;
        k = k * (a / d) % p;
    }
    if(k == b) return res;
    unordered_map<LL, LL> mp;
    LL x = 1, y, M = sqrt(p) + 1;
    for(int i = 0; i < M; i += 1, x = x * a % p) mp[b * x % p] = i;
    y = k * x % p;
    for(int i = 1; i <= M; i += 1, y = y * x % p)
        if(mp.count(y)) return res + i * M - mp[y];
    return -1;
}
