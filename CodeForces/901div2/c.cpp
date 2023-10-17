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
        ll n, m; cin >> n >> m;
        ll g = __gcd(n, m);
        n /= g, m /= g;
        if(__builtin_popcountl(m) > 1){
            cout << "-1\n";
            continue;
        }
        n %= m;
        ll ans = 0;
        rep(b, 1, 35){
            if((1LL << b) > m || n <= 0) break;
            ll unit = m / (1LL << b);
            ll times = n / unit;
            ans += times * ((1LL << b) - 1) * unit;
            n -= times * unit;
        }
        ans *= g;
        cout << ans << nL;
    }
    
    
    return 0;
}
