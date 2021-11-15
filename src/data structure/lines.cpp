struct line{
    static bool Q;
    mutable LL k, m, p;
    bool operator<(const line& o)const{
        return Q ? p < o.p : k < o.k;
    }
};
bool line::Q = false;
struct lines : multiset<line> {
    //(for doubles, use inf = 1/.0, div(a,b) = a/b)
    const LL inf = LLONG_MAX;
    LL div(LL a, LL b){
        return a / b - ((a ^ b) < 0 and a % b);
    }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, false;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(LL k, LL m) {
        line::Q = false;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() and isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() and (--x)->p >= y->p)
        isect(x, erase(y));
    }
    LL query(LL x) {
        line::Q = true;
        auto l = lower_bound({0, 0, x});
        return l->k * x + l->m;
    }
};