void fwt(vector<LL>& v, int inverse = false){
    int n = v.size();
    for(int i = 1; i < n; i <<= 1)
        for(int j = 0; j < n; j += i << 1)
            for(int k = 0; k < i; k += 1){
                LL& x = v[j + k], &y = v[i + j + k];
                tie(x, y) = inverse ? make_pair((x + y) / 2, (x - y) / 2) : make_pair(x + y, x - y);//xor
                x = inverse ? x - y : x + y;//and
                y = inverse ? y - x : x + y;//or
            }
}