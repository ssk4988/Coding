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
        ll a, b, c; cin >> a >> b >> c;
        ll ans = 0;
        if(2 * a <= b){
            ll maxa = c / a;
            ans = maxa;
        }
        else{
            // a = 0
            ll b0 = c / b;
            ll a0 = 2 * b0 - 1;
            ans = max(ans, a0);
            if(c >= a){
                ll b1 = (c - a) / b;
                ll a1 = 2 * b1 + 1;
                ans = max(ans, a1);
            }
        }
        // ll best = min(a, b);
        // ll cnt = c / best;
        // cnt--;
        // cnt = max(cnt, 0LL);
        cout << "Case #" << (cn + 1) << ": " << ans << nL;
    }
    
    return 0;
}
