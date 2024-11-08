#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
// using vd = vector<ld>;
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

const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> grid(n);
    rep(i, 0, n){
        cin >> grid[i];
    }
    // num non-. in string
    auto sc = [](string &s) -> int {
        int non = 0;
        for(char c : s) if(c != '.') non++;
        return non;
    };
    sort(all(grid), [&](string &a, string &b) -> bool {return sc(a) > sc(b); });
    int rows = 0, filled = 0, onlya = 0, onlyb = 0;

    while(rows < n){
        if(sc(grid[rows]) != 2) break;
        filled += 2;
        rows++;
    }
    int prefilled = 0, added = 0;
    rep(i, 0, n){
        bool a = false, b = false;
        rep(j, 0, n){
            if(grid[j][i] == 'A') a = true;
            if(grid[j][i] == 'B') b = true;
        }
        if(a && !b) onlya++;
        if(b && !a) onlyb++;
        prefilled += a + b;
    }
    vector<vector<vl>> dp(n + 1, vector<vl>(n + 1, vl(n + 1))); // [rows completed][cols with no A (exc)][cols with no B (exc)]
    dp[rows][onlyb][onlya] = 1;
    rep(i, rows, n){
        bool a = false, b = false;
        rep(j, 0, n){
            if(grid[i][j] == 'A') a = true;
            if(grid[i][j] == 'B') b = true;
        }
        rep(j, 0, n + 1){
            rep(k, 0, n + 1){
                if((prefilled + added + j + k) % 2 != 0) continue;
                int l = n - (prefilled + added + j + k) / 2;
                if(dp[i][j][k] == 0) continue;
                if(b){
                    if(j) dp[i+1][j-1][k] = mod(dp[i+1][j-1][k] + mod((j-1) * dp[i][j][k]));
                    if(l) dp[i+1][j][k+1] = mod(dp[i+1][j][k+1] + mod(l * dp[i][j][k]));
                }
                else if(a){
                    if(k) dp[i+1][j][k-1] = mod(dp[i+1][j][k-1] + mod((k-1) * dp[i][j][k]));
                    if(l) dp[i+1][j+1][k] = mod(dp[i+1][j+1][k] + mod(l * dp[i][j][k]));
                }
                else{
                    if(j && k) dp[i+1][j-1][k-1] = mod(dp[i+1][j-1][k-1] + mod(mod(j * k) * dp[i][j][k]));
                    if(l && j) dp[i+1][j][k] = mod(dp[i+1][j][k] + mod(mod(l * j) * dp[i][j][k]));
                    if(l && k) dp[i+1][j][k] = mod(dp[i+1][j][k] + mod(mod(l * k) * dp[i][j][k]));
                }
            }
        }
        added += !a + !b;
    }
    rep(i, 0, n + 1){
        rep(j, 0, n + 1){
            rep(k, 0, n + 1){
                if(dp[i][j][k])cout << "dp[" << i << "][" << j << "][" << k << "]=" << dp[i][j][k] << nL;
            }
        }
    }
    cout << dp[n][0][0] << nL;
    rep(i, 0, n) cout << grid[i] << nL;
    
    return 0;
}
