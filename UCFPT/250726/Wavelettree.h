struct WaveletTree {
    int n; vvi bv;
    WaveletTree(vl a, ll max_val) :
    n(sz(a)), bv(1+__lg(max_val), {{}}) {
        vl nxt(n);
        for(int h = sz(bv); h--; ) {
            vector<bool> b(n);
            rep(i, 0, n) b[i] = ((a[i] >> h)&1);
            bv[h] = vi(n+1);
            rep(i, 0, n) bv[h][i+1] = bv[h][i] + !b[i];
            array it{begin(nxt), begin(nxt) + bv[h][n]};
            rep(i, 0, n) *it[b[i]]++ = a[i];
            swap(a, nxt);
        }
    }
    ll kth(int l, int r, int k) {
        ll res = 0;
        for(int h = sz(bv); h--;) {
            int l0 = bv[h][l], r0 = bv[h][r];
            if(k < r0-l0) l = l0, r = r0;
            else k -= r0-l0, res |= 1ULL << h, l += bv[h][n] - l0, r += bv[h][n] - r0;
        }
        return res;
    }
    int count(int l, int r, ll ub) {
        int res = 0;
        for(int h = sz(bv); h--;) {
            int l0 = bv[h][l], r0 = bv[h][r];
            if((~ub >> h) & 1) l = l0, r = r0;
            else res += r0-l0, l += bv[h][n]-l0,
            r += bv[h][n] - r0;
        }
        return res;
    }
};
