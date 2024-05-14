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
    while(true){
        string str; cin >> str;
        if(str == "0") break;
        int n = sz(str);
        const int oo = 1e9;
        vvi dp(1 << n, vi(n, oo));
        rep(i, 0, n){
            dp[1 << i][i] = min((str[i] - 'A' + 26) % 26, ('A' - str[i] + 26) % 26) + 1;
        }
        rep(mask, 0, 1 << n){
            rep(last, 0, n){
                if(dp[mask][last] == oo) continue;
                int taps = 0;
                rep(nxt, last+1, n){
                    if((mask >> nxt) & 1) taps++;
                    else {
                        int cost = min((str[nxt] - str[last] + 26) % 26, (str[last] - str[nxt] + 26) % 26);
                        dp[mask | (1 << nxt)][nxt] = min(dp[mask | (1 << nxt)][nxt], cost + taps + 1 + dp[mask][last]);
                    }
                }
                taps = 0;
                for(int nxt = last; nxt >= 0; nxt--) {
                    if((mask >> nxt) & 1) taps++;
                    else {
                        int cost = min((str[nxt] - str[last] + 26) % 26, (str[last] - str[nxt] + 26) % 26);
                        dp[mask | (1 << nxt)][nxt] = min(dp[mask | (1 << nxt)][nxt], cost + taps + 1 + dp[mask][last]);
                    }
                }
            }
        }
        int ans = oo;
        rep(i, 0, n) ans = min(ans, dp.back()[i]);
        cout << ans << "\n";
    }
    
    return 0;
}
