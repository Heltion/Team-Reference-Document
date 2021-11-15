LL mul(LL a, LL b, LL p){
    return (a * b - (LL)(a / (long double)p * b + 1e-3) * p + p) % p;
}