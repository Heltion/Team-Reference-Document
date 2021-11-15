vector<int> duval(const vector<int>& s) {
    int n = s.size();
    vector<int> res;
    for(int i = 0, j, k; i < n; ) {
        j = i + 1, k = i;
        for(; j < n and s[k] <= s[j]; j += 1)
            if(s[k] < s[j]) k = i;
            else k += 1;
        for(; i <= k; i += j - k) res.push_back(i);
    }
    return res;
}