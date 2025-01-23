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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; ll x; cin >> n >> x;
        vl pref{0};
        rep(i, 0, n){
            int v; cin >> v;
            pref.pb(pref.back() ^ v);
        }
        int ans = -1;
        vl cands{x};
        rep(b, 0, 30){
            if((x >> b) & 1) {
                ll c = ~((1 << b)-1) & x;
                c ^= 1 << b;
                c += (1 << b) -1;
                assert(c <= x);
                cands.pb(c);
            }
        }
        for(ll c : cands){
            if((pref.back() & c) != pref.back()) continue;
            int res = 0;
            for(ll v : pref) if((v & c) == v) res++;
            ans = max(ans, res-1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
