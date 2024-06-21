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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        ll mnpref = 0, pref = 0;
        rep(i, 0, n){
            cin >> a[i];
            pref += a[i];
            mnpref = min(mnpref, pref);
        }
        ll ans = 0;
        rep(i, 0, n){
            ans += a[i];
            if(ans == mnpref) ans = abs(ans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
