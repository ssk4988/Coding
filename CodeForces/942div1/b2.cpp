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
    // const int LIM = 2e6 + 10;
    // vvi divs(LIM);
    // rep(i, 1, LIM){
    //     for(int j = i; j < LIM; j += i){
    //         divs[j].pb(i);
    //     }
    // }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        // not actually a
        int ans = 0;
        // set<pi> s;
        rep(a, 1, n+1){
            int blim = min(m, n / a);
            int pnt = 0;
            for(int b = 1; b <= m; b++){
                if(ll(a) * (a + b) > n || ll(b) * (a + b) > m) break;
                if(__gcd(a, b) != 1) continue;
                int lim = min(n / a, m / b);
                ans += (lim) / (a + b);
                // for(int g = a + b; g; g += a + b){
                //     if(ll(g) * a > n || ll(g) * b > m) break;
                //     ans++;
                //     // cout << (g*a) << " " << (g*b) << "\n";
                //     // s.insert({g*a, g*b});
                // }
            }
        }
        cout << ans << "\n";
        // for(auto [a,b] : s){
        //     cout << a << "," << b << "\n";
        // }
    }


    return 0;
}
