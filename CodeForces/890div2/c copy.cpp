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
        int n; ll k; cin >> n >> k;
        vl a(n);
        ll ans = 0;
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n){
            ll lo = a[i], hi = a[i] + k;
            while(lo < hi){
                ll mid = lo + (hi - lo + 1) / 2;
                ll cost = 0;
                bool foundbigger = false;
                rep(j, i, n){
                    if(j > i && a[j] >= mid - (j - i)){
                        foundbigger = true;
                        break;
                    }
                    cost += mid - (j - i) - a[j];
                }
                if(foundbigger && cost <= k){
                    lo = mid;
                }
                else hi =mid - 1;
            }
            ans = max(lo, ans);
        }
        cout << ans << nL;
    }
    
    return 0;
}
