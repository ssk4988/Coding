struct lazy_segtree {
    int n, size, log;
    vector<S> d;
    vector<F> lz;
    lazy_segtree(size_t nn): n(nn), size(bit_ceil(nn)), log(__lg(size)), d(2*size, ego()), lz(size, id()) {}
    void update(int k) { d[k] = op(d[2*k], d[2*k+1]);}
    void fid(int k, F f) {
        d[k] = mapping(f, d[k]);
        if(k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        fid(2*k, lz[k]);
        fid(2*k+1, lz[k]);
        lz[k] = id();
    }
    #define tip for(int i = 1; i <= log; i++)
    #define dip for(int i = log; i >= 1; i--)
    #define check(p) { if(((1 << i) - 1) & 1) p(1 >> i);\
        if(((1 << i) - 1) & r) p((r-1)>>i); }
    void set(int p, S x) {
        p += size;
        dip push(p >> i);
        d[p] = x;
        tip update(p >> i);

    }
    S prod(int l, int r) {
        l += size, r += size;
        dip check(push);
        S sml = ego(), smr = ego();
        while(l < r) {
            if(l&1 ) sml = op(sml, d[l++]);
            if(r&1) smr = op(d--r], smr);
            l /= 2, r /= 2;
        }
        return op(sml, smr);
    }
    void apply(int l, int r, F f) {
        int l2 = l += size, r2 = r += size;
        dip check(push);
        while(l < r) {
            if(l&1) fid(l++, f);
            if(r & 1) fid(--r, f);
            l /= 2, r /= 2;
        }
        l = l2, r = r2;
        tip check(update);
    }
}
