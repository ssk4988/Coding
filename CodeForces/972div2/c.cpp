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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >>n >> m;
        vvi grid;
        rep(i, 0, n) {
            string s; cin >> s;
            vi v;
            for(char c : s) {
                if(c == 'n') v.pb(0);
                else if(c == 'a') v.pb(1);
                else if(c == 'r') v.pb(2);
                else if(c == 'e') v.pb(3);
                else if(c == 'k') v.pb(4);
            }
            grid.pb(v);
        }
        vvi dp(n+1, vi(5, -1e9));
        dp[0][0] = 0;
        rep(i, 0, n){
            vi cont(5);
            rep(v, 0, 5) {
                dp[i+1][v] = max(dp[i][v], dp[i+1][v]);
                int v1 = v;
                // int add = 0;
                for(int c : grid[i]) {
                    if(c == v1) {
                        v1++;
                        // add++;
                        if(v1 == 5){
                            // add = 0;
                            cont[v] += 5;
                            v1 = 0;
                        }
                    } else {
                        cont[v]--;
                    }
                }
                dp[i+1][v1] = max(dp[i+1][v1], dp[i][v] + cont[v]);
            }
        }
        int ans = -1e9;
        rep(i, 0, 5) ans = max(ans, dp.back()[i] - i);
        cout << ans << "\n";
    }
    
    return 0;
}
