struct P{
    LL x, y;
};
LL sqrt(LL n, LL p){
    if(n == 0) return 0;
    if(power(n, (p ^ 1) >> 1, p) != 1) return -1;
    LL x, w;
    do x = rand(), w = (x * x + p - n) % p;
    while(power(w, (p ^ 1) >> 1, p) == 1);
    auto mul = [&](P A, P B)->P{
        return {(A.x * B.x + A.y * B.y % p * w) % p, (A.x * B.y + A.y * B.x) % p};
    };
    P a = {x, 1}, res = {1, 0};
    for(LL r = (p + 1) >> 1; r; r >>= 1, a = mul(a, a))
        if(r & 1) res = mul(res, a);
    return res.x;
}