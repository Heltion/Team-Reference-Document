vector<int> manacher(const string& s){
  int n = s.size();
  vector<int> p(n);
  for(int i = 0, r = 0, m = 0; i < n; i += 1){
      p[i] = i < r ? min(p[m * 2 - i], r - i) : 1;
      while(i >= p[i] and i + p[i] < n and s[i - p[i]] == s[i + p[i]]) p[i] += 1;
      if(i + p[i] > r) m = i, r = i + p[i];
  }
  return p;
}