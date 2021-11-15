LD simpson(function<LD(LD)> f, LD L, LD R){
    return (f(L) + f((L + R) / 2) * 4 + f(R)) * (R - L) / 6;
}
LD simpson(function<LD(LD)> f, LD L, LD R, LD eps){
    function<LD(LD, LD, LD, LD)> rec = [&](LD L, LD R, LD S, LD e){
        LD M = (L + R) / 2;
        LD S1 = simpson(f, L, M), S2 = simpson(f, M, R);
        if(abs(S1 + S2 - S) <= 15 * e or R - L <= eps)
            return S1 + S2;
        return rec(L, M, S1, e / 2)  + rec(M, R, S2, e / 2);
    };
    return rec(L, R, simpson(f, L, R), eps);
}