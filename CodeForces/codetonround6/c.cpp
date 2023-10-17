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
        int n, k; cin >> n >> k;
        vvi occ(k + 1);
        rep(i, 0, n){
            int a; cin >> a;
            occ[a].pb(i);
        }
        vi ans(k + 1);
        int mn = INT_MAX, mx = INT_MIN;
        for(int i = k; i > 0; i--){
            if(sz(occ[i]) == 0) continue;
            for(int j : occ[i]){
                mn = min(mn, j);
                mx = max(mx, j);
            }
            ans[i] = 2 * (1 + mx - mn);
        }
        rep(i, 1, k + 1){
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
