struct FT {
    vector<ll> s;
    FT(int n)  : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if(sum <= 0) return -1;
        int pos = 0;
        for(int pw = 1 << 25; pw; pw >>= 1) {
            if(pos + pw <= sz(s) && s[pos + pw-1] < sum) pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};
