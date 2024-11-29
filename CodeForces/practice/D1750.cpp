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

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vi pf;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        int m1 = a[0];
        rep(i, 2, 1e5){
            if(m1 % i == 0){
                while(m1 % i == 0) m1 /= i;
                pf.pb(i);
            }
        }
        if(m1 > 1) pf.pb(m1);
        ll ways = 1;
        rep(i, 1, n){
            if((a[i-1] % a[i] != 0)){
                ways = 0;
                break;
            }
            int div = a[i-1] / a[i];
            vi p;
            for(int ps : pf) if(div % ps == 0) p.pb(ps);
            ll cnt = 0;
            rep(mask, 0, 1 << sz(p)){
                int mult = 1;
                rep(j, 0, sz(p)){
                    if((mask >> j) & 1) mult *= p[j];
                }
                cnt += (m/a[i])/mult * (__builtin_popcount(mask)&1 ? -1 : 1);
            }
            // cout << ways << " " << cnt << " " << div << "\n";
            (ways *= cnt) %= MOD;
        }
        cout << ways << "\n";
    }
    
    return 0;
}
