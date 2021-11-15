vector<int> cartesianTree(const vector<int>& v) {
    int n = v.size();
    vector<int> p(n, -1);
    stack<int> s;
    for (int i = 0, t = -1; i < n; i += 1) {
        for(t = -1; not s.empty() and v[s.top()] > v[i]; s.pop()) t = s.top();
        if (not s.empty()) p[i] = s.top();
        if (t != -1) p[t] = i;
        s.push(i);
    }
    return p;
}