#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)


const ll mod = (119 << 23) + 1, root = 62;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; b = b*b%mod, e /= 2) 
        if(e&1) res = res * b % mod;
    return res;
}
typedef vector<ll> vl;
void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for(static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, mod >> s)};
        rep(i,k,2*k) rt[i] = rt[i/2] * z[i&1] % mod;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i/2] | (i&1) << L) / 2;
    rep(i,0,n) if(i < rev[i]) swap(a[i], a[rev[i]]);
    for(int k = 1; k < n; k *= 2) 
        for(int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i+j];
            a[i+j+k] = ai-z + (z > ai ? mod : 0);
            ai += (ai + z >= mod ? z-mod : z);
        }
}
vl conv(const vl &a, const vl &b) {
    if(a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = modpow(n, mod-2);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i, 0, n)
        out[-i&(n-1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, c; cin >> n >> c;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    vl cur(c+1);
    cur[0] = 1;
    ll mx = *max_element(all(a));
    for(ll b = 1; b <= mx; b *= 2) {
        vl nxt(c+1);
        rep(i, 0, n) {
            ll v = ((a[i]-1) / b + 1);
            if(v <= c) nxt[v] = 1;
        }
        vl res = conv(cur, nxt);
        if(sz(res) > c+1) res.resize(c+1);
        if(res[c]) {
            cout << "YES\n";
            return 0;
        }
        rep(i, 0, sz(res)) {
            if(res[i] != 0) res[i] = 1;
        }
        cur = res;
    }
    rep(i, 0, sz(cur)) {
        if(cur[i]) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}
