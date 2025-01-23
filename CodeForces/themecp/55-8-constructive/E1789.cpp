#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl s(n);
        rep(i, 0, n) cin >> s[i];
        int m = s.back();
        vl prefcont(m+2);
        int l = 1;
        while(l <= m) {
            int r = l;
            while(r <= m && m / r == m / l && (m-1)/r == (m-1) / l) r++;
            ll cont = 0;
            rep(i, l, r) (cont += i) %= mod;
            int fl = m / l, cl = (m-1) / l + 1;
            if(fl == cl) {
                for(int i = fl; i <= m; i += fl) {
                    (prefcont[i] += cont) %= mod;
                    (prefcont[i+1] -= cont) %= mod;
                }
            } else {
                assert(fl + 1 == cl);
                (prefcont[1] += cont) %= mod;
                (prefcont[m+1] -= cont) %= mod;
                ll lim = ll(fl) * cl;
                for(int il = 1, ir = fl; il <= m && il <= lim; il += cl, ir += fl) {
                    (prefcont[il] -= cont) %= mod;
                    (prefcont[min(ir, m+1)] += cont) %= mod;
                }
            }
            l = r;
        }
        ll ans = 0;
        rep(i, 1, sz(prefcont)){
            (prefcont[i] += prefcont[i-1]) %= mod;
        }
        for(int i : s){
            (ans += prefcont[i]) %= mod;
        }
        ans = (ans % mod + mod) % mod;
        cout << ans << "\n";
    }    
    
    return 0;
}
