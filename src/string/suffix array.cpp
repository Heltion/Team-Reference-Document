struct Suffix_Array : vector<int> {
    vector<int> rank, lcp;
    Suffix_Array(const string& s) : vector<int>(s.size()), rank(s.size()), lcp(s.size()){
        int n = s.size(), k = 128;
        vector<int> cnt(max(n, k), 0), p(n);
        for (int i = 0; i < n; i += 1) cnt[rank[i] = s[i]] += 1;
        for (int i = 1; i < k; i += 1) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i -= 1) at(cnt[rank[i]] -= 1) = i;
        for (int h = 1; h <= n; h <<= 1) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i += 1) cnt[rank[i]] += 1;
            for (int i = 1; i < k; i += 1) cnt[i] += cnt[i - 1];
            k = 0;
            for (int i = n - h; i < n; i += 1) p[k ++] = i;
            for (int i = 0; i < n; i += 1) if (at(i) >= h) p[k ++] = at(i) - h;
            for (int i = n - 1; i >= 0; i -= 1) at(cnt[rank[p[i]]] -= 1) = p[i];
            p.swap(rank);
            rank[at(0)] = 0;
            k = 1;
            for (int i = 1; i < n; i += 1) {
                if (p[at(i)] != p[at(i - 1)] or at(i - 1) + h >= n or p[at(i) + h] != p[at(i - 1) + h]) k += 1;
                rank[at(i)] = k - 1;
            }
            if (k == n) break;
        }
        for (int i = 0, k = 0; i < n; i += 1) {
            if (k) k -= 1;
            if (rank[i]) while (s[i + k] == s[at(rank[i] - 1) + k]) k += 1;
            lcp[rank[i]] = k;
        }
    }
};