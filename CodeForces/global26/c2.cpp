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

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        ll mnpref = 0, pref = 0;
        map<ll, ll> dp;
        dp[0] = 1;
        rep(i, 0, n){
            cin >> a[i];
            pref += a[i];
            mnpref = min(mnpref, pref);
        }
        rep(i, 0, n){
            map<ll, ll> newdp;
            for(auto [key, val] : dp){
                ll nkey = key + a[i];
                newdp[nkey] = (newdp[nkey] + val) % MOD;
                if(nkey == mnpref || nkey >= 0){
                    nkey = abs(nkey);
                    newdp[nkey] = (newdp[nkey] + val) % MOD;
                }
            }
            swap(dp, newdp);
        }
        cout << dp.rbegin()->second << "\n";
    }
    
    return 0;
}
