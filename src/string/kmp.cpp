vector<int> kmp(const string& s){
  int n = s.size();
  vector<int> p(n);
  for(int i = 1, j = 0; i < n; i += 1){
    while(j and s[i] != s[j]) j = p[j - 1];
    if(s[i] == s[j]) j += 1;
    p[i] = j;
  }
  return p;
}