void pollard_rho(LL n){
    if(n == 1) return;
    if(miller_rabin(n)) return;//find a prime factor
    LL d = n;
    while(d == n){
        d = 1;
        for(LL k = 1, y = 0, x = 0, s = 1, c = rand() % n; d == 1; k <<= 1, y = x, s = 1)
            for(int i = 1; i <= k; i += 1){
                x = (mul(x, x, n) + c) % n;
                s = mul(s, abs(x - y), n);
                if(not(i % 127) or i == k){
                    d = gcd(s, n);
                    if(d != 1) break;
                }
            }
    }
    pollard_rho(d);
    pollard_rho(n / d);
};