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

const ll MOD = 1e9 + 7;
const int LIM = 1e9;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn,0, nc){
        int n; cin >> n;
        string str; cin >> str;
        vl a(n);
        vl adj(n);
        rep(i, 0, n) {
            cin >> a[i];
            adj[i] = a[i];
            if(i) adj[i] += a[i-1];
        }
        vector<vector<vl>> dp(n, vector<vl>(2, vl(n+1, -1)));
        auto go = [&](int idx, int isp, int lastps, auto &&go) -> ll {
            if((isp && str[idx] == 'S') || (!isp && str[idx] == 'P')) return 0;
            if(idx == n-1 && !isp && abs(a[idx]) > LIM) return 0;
            if(idx == n-1 && isp && lastps != n && a[idx] != adj[lastps]) return 0;
            if(idx == 0 && isp && abs(a[idx]) > LIM) return 0;
            ll &ans = dp[idx][isp][lastps];
            if(ans != -1) return ans;
            // cout << idx << " " << isp << " " << lastps << " not rejected\n";
            if(idx == n-1) return ans = 1;
            ans = 0;
            if(isp) {
                // add s
                if(lastps == n || adj[idx+1] == adj[lastps]) ans = (ans + go(idx+1, 0, idx+1, go)) % MOD;
                // add p
                if(abs(a[idx+1] - a[idx]) <= LIM) ans = (ans + go(idx+1, 1, lastps, go)) % MOD;
            }
            if(!isp) {
                // add s
                if(abs(a[idx+1] - a[idx]) <= LIM) ans = (ans + go(idx+1, 0, lastps, go)) % MOD;
                // add p
                assert(lastps != n);
                if(abs(adj[lastps] - adj[idx+1]) <= 2 * LIM) ans = (ans + go(idx+1, 1, lastps, go)) % MOD;
            }
            // if(ans) cout << idx << " " << isp << " " << lastps << " " << ans << "\n";
            return ans;
        };
        ll ans = (go(0, 1, n, go) + go(0, 0, 0, go)) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
