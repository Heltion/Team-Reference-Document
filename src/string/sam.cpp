constexpr int maxc = 26;
struct State{
    int len, link, next[maxc];
    State(int len) : len(len), link(-1){
        fill(next, next + maxc, -1);
    }
};
struct SAM : vector<State>{
    int last;
    SAM() : last(0){
        emplace_back(0);
    };
    void extend(int c){
        int cur = size();
        emplace_back(at(last).len + 1);
        int p = last;
        for(; ~p and at(p).next[c] == -1; p = at(p).link) at(p).next[c] = cur;
        if(p == -1) back().link = 0;
        else{
            int q = at(p).next[c];
            if(at(p).len + 1 == at(q).len) back().link = q;
            else{
                int clone = size();
                push_back(at(q));
                back().len = at(p).len + 1;
                for(; ~p and at(p).next[c] == q; p = at(p).link) at(p).next[c] = clone;
                at(q).link = at(cur).link = clone;
            }
        }
        last = cur;
    }
};