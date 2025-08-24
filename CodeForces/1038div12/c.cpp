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
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi p(n, vi(2));
        vector<vii> c(2);
        rep(i, 0, n) {
            rep(j, 0, 2) {
                cin >> p[i][j];
                c[j].pb({p[i][j], i});
            }
        }
        vi mask(n);
        vvi bit(4);
        rep(i, 0, 2) {
            sort(all(c[i]));
            rep(j, n/2, n) {
                auto [_, idx] = c[i][j];
                mask[idx] |= 1 << i; 
            }
        }
        rep(i, 0, n) {
            bit[mask[i]].pb(i);
        }
        rep(i, 0, 2) {
            rep(j, 0, sz(bit[i])) {
                cout << bit[i][j]+1 << " " << bit[3^i][j]+1 << "\n";
            }
        }
    }
    
    return 0;
}
