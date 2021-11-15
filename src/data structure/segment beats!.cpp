#define tm ((tl + tr) >> 1)
struct Node{
    static constexpr LL inf = __LONG_LONG_MAX__;
    Node *ls, *rs;
    LL mx, smx, cmx, mn, smn, cmn, sm, tmx, tmn, tadd;
    Node() {
        tmx = -inf;
        tmn = inf;
        tadd = 0;
    }
    void init(LL x) {
        mx = mn = sm = x;
        cmx = cmn = 1;
        smx = tmx = -inf;
        smn = tmn = inf;
        tadd = 0;
    }
    void push_up() {
        sm = ls->sm + rs->sm;
        mx = max(ls->mx, rs->mx);
        smx = max(ls->mx == mx ? ls->smx : ls->mx, rs->mx == mx ? rs->smx : rs->mx);
        cmx = (ls->mx == mx ? ls->cmx : 0) + (rs->mx == mx ? rs->cmx : 0);
        mn = min(ls->mn, rs->mn);
        smn = min(ls->mn == mn ? ls->smn : ls->mn, rs->mn == mn ? rs->smn : rs->mn);
        cmn = (ls->mn == mn ? ls->cmn : 0) + (rs->mn == mn ? rs->cmn : 0);
    }
    void add(int tl, int tr, LL x) {
        sm += (tr - tl) * x;
        mx += x;
        if (smx != -inf) smx += x;
        if (tmx != -inf) tmx += x;
        mn += x;
        if (smn != inf) smn += x;
        if (tmn != inf) tmn += x;
        tadd += x;
    }
    void chmin(LL x) {
        if (mx <= x) return;
        sm += (x - mx) * cmx;
        if (smn == mx) smn = x;
        if (mn == mx) mn = x;
        if (tmx > x) tmx = x;
        mx = tmn = x;
    }
    void chmax(LL x) {
        if (mn >= x) return;
        sm += (x - mn) * cmn;
        if (smx == mn) smx = x;
        if (mx == mn) mx = x;
        if (tmn < x) tmn = x;
        mn = tmx = x;
    }
    void push_down(int tl, int tr) {
        if (tadd) {
            ls->add(tl, tm, tadd);
            rs->add(tm, tr, tadd);
            tadd = 0;
        }
        if (tmn != inf) {
            ls->chmin(tmn);
            rs->chmin(tmn);
            tmn = inf;
        }
        if (tmx != -inf) {
            ls->chmax(tmx);
            rs->chmax(tmx);
            tmx = -inf;
        }
    }
    void chmin(int tl, int tr, int L, int R, LL x) {
        if (mx <= x) return;
        if (tl >= L and tr <= R and smx < x) return chmin(x);
        push_down(tl, tr);
        if (L < tm) ls->chmin(tl, tm, L, R, x);
        if (R > tm) rs->chmin(tm, tr, L, R, x);
        push_up();
    }
    void chmax(int tl, int tr, int L, int R, LL x) {
        if (mn >= x) return;
        if (tl >= L and tr <= R and smn > x) return chmax(x);
        push_down(tl, tr);
        if (L < tm) ls->chmax(tl, tm, L, R, x);
        if (R > tm) rs->chmax(tm, tr, L, R, x);
        push_up();
    }
    void add(int tl, int tr, int L, int R, LL x) {
        if (tl >= L and tr <= R) return add(tl, tr, x);
        push_down(tl, tr);
        if (L < tm) ls->add(tl, tm, L, R, x);
        if (R > tm) rs->add(tm, tr, L, R, x);
        push_up();
    }
    LL sum(int tl, int tr, int L, int R) {
        if (tl >= L and tr <= R) return sm;
        push_down(tl, tr);
        LL res = 0;
        if (L < tm) res += ls->sum(tl, tm, L, R);
        if (R > tm) res += rs->sum(tm, tr, L, R);
        return res;
    }
};
struct Segment_Tree_Beats : vector<Node>{
    Node* root;
    int N;
    Segment_Tree_Beats(int N) : vector<Node>(2 * N - 1), N(N){}
    void init(vector<LL>& a) {
        int p = 0;
        function<void(Node*&, int, int)> build = [&](Node*& v, int tl, int tr) {
            v = &at(p ++);
            if (tl + 1 == tr) return v->init(a[tm]);
            build(v->ls, tl, tm);
            build(v->rs, tm, tr);
            v->push_up();
        };
        build(root, 0, N);
    }
    void chmin(int l, int r, LL b) {
        root->chmin(0, N, l, r, b);
    }
    void chmax(int l, int r, LL b) {
        root->chmax(0, N, l, r, b);
    }
    void add(int l, int r, LL b) {
        root->add(0, N, l, r, b);
    }
    LL sum(int l, int r) {
        return root->sum(0, N, l, r);
    }
};