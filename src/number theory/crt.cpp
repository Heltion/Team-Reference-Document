pair<LL, LL> crt(const vector<pair<LL, LL>>& p){
    __int128 A = 1, B = 0;
    for(auto [a, b] : p){
        LL x, y, d = exgcd(A, a, x, y);
        if((b - B) % d) return {-1, -1};
        B += (b - B) / d * x % (a / d) * A;
        A = A / d * a;
        B = (B % A + A) % A;
    }
    return {A, B};
}