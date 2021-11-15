struct P{
    R x, y;
    P operator - (const P& p){return {x - p.x, y - p.y};}
    R cross(const P& p){return x * p.y - y * p.x;}
};
vector<P> convex_hull(vector<P>& p){
    sort(p.begin(), p.end(), [](const P& A, const P& B){
        return A.x == B.x ? A.y < B.y : A.x < B.x;
    });
    vector<P> h;
    for(auto cur : p){
        while(h.size() >= 2 and (cur - h[h.size() - 2]).cross(h.back() - h[h.size() - 2]) >= 0) h.pop_back();
        h.push_back(cur);
    }
    int tmp = h.size();
    reverse(p.begin(), p.end());
    for(auto cur : p){
        while(h.size() - tmp >= 1 and (cur - h[h.size() - 2]).cross(h.back() - h[h.size() - 2]) >= 0) h.pop_back();
        h.push_back(cur);
    }
    h.pop_back();
    return h;
}