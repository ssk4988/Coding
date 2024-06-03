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
    ll n, m, d; cin >> n >> m >> d;
    vector<vl> grid(n, vl(m));
    set<ll> ss;
    rep(i, 0, n){
        rep(j, 0, m){
            cin >> grid[i][j];
            ss.insert(grid[i][j] % d);
        }
    }
    if(sz(ss) > 1){
        cout << -1 << "\n";
        return 0;
    }
    ll res = *ss.begin();
    ll ans = LLONG_MAX;
    for(ll t = res; t <= 1e5; t += d){
        ll cur = 0;
        // cout << t << "\n";
        rep(i, 0, n){
            rep(j, 0, m){
                cur += abs(grid[i][j] - t) / d;
            }
        }
        ans = min(ans, cur);
        if(t > 1e4) {
            break;
        }
        // if(cur == 0) cout << t << " " << res << "\n";
    }
    cout << ans << "\n";
    return 0;
}
