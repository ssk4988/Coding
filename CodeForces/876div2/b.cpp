#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vpi v(n);
        vvl occ(n + 1);
        rep(i, 0, n){
            cin >> v[i].f >> v[i].s;
            occ[v[i].f].pb(v[i].s);
        }
        ll ans = 0;
        rep(i, 1, n + 1){
            sort(all(occ[i]));
            reverse(all(occ[i]));
            rep(j, 0, min(i, sz(occ[i]))){
                ans += occ[i][j];
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
