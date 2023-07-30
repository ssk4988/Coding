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
        int n; cin >> n;
        map<int, ll> row, col, d1, d2;
        rep(i, 0, n){
            int x, y; cin >> x >> y;
            row[x]++;
            col[y]++;
            d1[x + y]++;
            d2[x - y]++;
        }
        ll ans = 0;
        for(auto [key, val] : row){
            ans += val * ll(val - 1);
        }
        for(auto [key, val] : col){
            ans += val * ll(val - 1);
        }
        for(auto [key, val] : d1){
            ans += val * ll(val - 1);
        }
        for(auto [key, val] : d2){
            ans += val * ll(val - 1);
        }
        cout << ans << nL;
    }
    
    return 0;
}