struct node{
    node* p;
    array<node*, 2> c;
    int rev, size, vsize;
    LL v, sum, vsum, add, vadd;
    node(){
        p = c[0] = c[1] = nullptr;
        size = 1;
        v = vsize = sum = vsum = add = vadd = rev = 0;
    }
    int d(){
        if(p){
            if(p->c[0] == this) return 0;
            if(p->c[1] == this) return 1;
        }
        return -1;
    }
    void flush(){
        if(~d()) p->flush();
        down();
    }
    void rotate(){
        int pd = d();
        auto pp = p, pc = c[not pd];
        p = pp->p; if(~pp->d()) pp->p->c[pp->d()] = this;
        pp->c[pd] = pc; if(pc) pc->p = pp;
        c[not pd] = pp; pp->p = this;
        pp->up();
    }
    void splay(){
        for(flush(); ~d(); rotate())
            if(~p->d()) (d() == p->d() ? p : this)->rotate();
        up();
    }
    void reverse(){
        rev ^= 1;
        swap(c[0], c[1]);
    }
    void addf(LL x){
        v += x;
        sum += size * x;
        vsum += vsize * x;
        add += x;
        vadd += x;
    }
    void change(node* c, int v){
        if(not v) c->addf(vadd);
        vsize += v ? c->size : -c->size;
        vsum += v ? c->sum : -c->sum;
        if(v) c->addf(-vadd);
    }
    void up(){
        size = 1 + vsize;
        sum = v + vsum;
        for(auto x : c) if(x){
            size += x->size;
            sum += x->sum;
        }
    }
    void down(){
        if(rev) for(auto x : c) if(x) x->reverse();
        if(add) for(auto x : c) if(x) x->addf(add);
        rev = add = 0;
    }
};
struct link_cut_tree : vector<node>{
    link_cut_tree(int n) : vector<node>(n){}
    node* get(int u){
        return data() + u;
    }
    void access(int u){
        for(node *v = get(u), *p = nullptr; v; p = v, v = v->p){
            v->splay();
            if(v->c[1]) v->change(v->c[1], 1);
            if(p) v->change(p, 0);
            v->c[1] = p;
            v->up();
        }
        get(u)->splay();
    }
    void make_root(int u){
        access(u);
        at(u).reverse();
    }
    void link(int u, int v){
        access(u);
        make_root(v);
        at(v).p = get(u);
        at(u).c[1] = get(v);
        at(u).up();
    }
    void cut(int u, int v){
        make_root(u);
        access(v);
        at(v).c[0]->p = nullptr;
        at(v).c[0] = nullptr;
        at(v).up();
    }
};