constexpr int maxc = 26;
struct State{
    int link, next[maxc];
    State() : link(0){
        fill(next, next + maxc, 0);
    }
};
struct AC : vector<State>{
    AC(){
        emplace_back();
    }
    int insert(const vector<int>& s){
        int p = 0;
        for(int c : s){
            if(not at(p).next[c]){
                at(p).next[c] = size();
                emplace_back();
            }
            p = at(p).next[c];
        }
        return p;
    }
    void init(){
        queue<int> q;
        q.push(0);
        while(not q.empty()){
            int u = q.front();
            q.pop();
            for(int i = 0; i < maxc; i += 1){
                int &s = at(u).next[i];
                if(not s) s = at(at(u).link).next[i];
                else{
                    at(s).link = u ? at(at(u).link).next[i] : 0;
                    q.push(s);
                }
            }
        }
    }
};