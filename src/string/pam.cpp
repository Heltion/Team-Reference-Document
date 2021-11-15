constexpr int maxc = 26;
struct State{
    int sum, len, link, next[maxc];
    State(int len) : len(len){
        sum = link = 0;
        fill(next, next + maxc, 0);
    }
};
struct PAM : vector<State>{
    int last;
    vector<int> s;
    PAM() : last(0){
        emplace_back(0);
        emplace_back(-1);
        at(0).link = 1;
    }
    int get_link(int u, int i){
        while(i < at(u).len + 1 or s[i - at(u).len - 1] != s[i]) u = at(u).link;
        return u;
    }
    void extend(int i){
        int cur = get_link(last, i);
        if(not at(cur).next[s[i]]){
            int now = size();
            emplace_back(at(cur).len + 2);
            back().link = at(get_link(at(cur).link, i)).next[s[i]];
            back().sum = at(back().link).sum + 1;
            at(cur).next[s[i]] = now;
        }
        last = at(cur).next[s[i]];
    }
};