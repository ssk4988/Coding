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
    const int LIM = 1e5+10;
    vi prime(LIM, 1), lp(LIM);
    rep(p, 2, LIM) {
        if(!prime[p]) continue;
        lp[p] = p;
        for(int i = p*2; i < LIM; i += p) {
            prime[i] = 0;
            lp[i] = p;
        }
    }
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi occ(n+1);
        for(int i = n; i >= 2; i--) {
            occ[lp[i]].pb(i);
        }
        vi ans(n+1);
        ans[1] = 1;
        rep(i, 2, n+1) {
            rep(j, 0, sz(occ[i])) {
                ans[occ[i][j]] = occ[i][(j+1)%sz(occ[i])];
            }
        }
        rep(i, 1, n+1) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
