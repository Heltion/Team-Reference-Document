LL exgcd(LL a, LL b, LL& x, LL& y){
    if(not b) return x = 1, y = 0, a;
    LL d = exgcd(b, a % b, x, y), t = x;
    return x = y, y = t - a / b * y, d;
};