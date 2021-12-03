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

constexpr int k, w1;
void fwt(vector<LL>& v, int n, bool inverse = false){
    vector<LL> t(k), w(k);
    for(int i = 0; i < k; i += 1) w[i] = i ? w[i - 1] * w1 % mod : 1;
    for(int i = 1; i < n; i *= k){
        for(int l = 0; l < n; l += i * k){
            for(int j = l; j < l + i; j += 1){
                for(int a = 0; a < k; a += 1) 
                    for(int b = t[a] = 0; b < k; b += 1) 
                        t[a] = (t[a] + v[j + b * i] * w[b * (k + (inverse ? a : -a)) % k]) %  mod;
                for(int a = 0; a < k; a += 1) v[j + a * i] = t[a];
            }
        }
    }
	if(inverse){
        LL inv = power(n, mod - 2);
        for(int i = 0; i < n; i += 1) F[i] = F[i] * inv % mod;
    }
}