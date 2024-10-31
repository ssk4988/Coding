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
    ll n; cin >> n;
    vi dp(n+1, -1);
    dp[0] = 0;
    auto go = [&](ll u, auto &&go) -> int {
        if(dp[u] != -1) return dp[u];
        auto &res = dp[u];
        res = u+10;
        ll u1 = u;
        while(u1){
            int d = u1 % 10;
            if(d) res = min(res, go(u-d, go) + 1);
            u1 /= 10;
        }
        return res;
    };
    rep(i, 1, n+1) {
        ll u1 = i;
        vi digs;
        go(i, go);
        while(u1){
            int d = u1 % 10;
            if(d) digs.pb(d);
            // if(d && dp[i] == 1 + dp[i - d]) cout << d << " ";
            u1 /= 10;
        }
        sort(all(digs));
        digs.erase(unique(all(digs)), end(digs));
        int d = digs.back();
        if(dp[i - d] + 1 != dp[i]) {
            cout << "breaker: " << i << ": ";
            for(int d1 : digs){
                if(dp[i - d1] + 1 == dp[i]) cout << d1 << " ";
                cout << endl;
            }
        }
        if(i <= min(n, 1350LL)) {
            cout << i << ": " << go(i, go) << " digs: ";
            // for(int d1 : digs){
            //     if(dp[i - d1] + 1 == dp[i]) cout << d1 << " ";
            // }
            cout << digs.back() << endl;
        }
    }
    
    return 0;
}
