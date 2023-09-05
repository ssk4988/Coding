#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define pb push_back
#define f first
#define s second

const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a, b, c; cin >> a >> b >> c;
    vector<vector<vector<vl>>> dp(a + 1, vector<vector<vl>>(b + 1, vector<vl>(c + 1, vl(3))));
    dp[1][0][0][0] = dp[0][1][0][1] = dp[0][0][1][2] = 1;
    rep(i, 0, a + 1){
        rep(j, 0, b + 1){
            rep(k, 0, c + 1){
                rep(l, 0, 3){
                    if(dp[i][j][k][l] == 0) continue;
                    if(i + 1 <= a && l != 0){
                        dp[i + 1][j][k][0] = mod(dp[i + 1][j][k][0] + dp[i][j][k][l]);
                    }
                    if(j + 1 <= b && l != 1){
                        dp[i][j+1][k][1] = mod(dp[i][j+1][k][1] + dp[i][j][k][l]);
                    }
                    if(k + 1 <= c && l != 2){
                        dp[i][j][k+1][2] = mod(dp[i][j][k+1][2] + dp[i][j][k][l]);
                    }
                }
            }
        }
    }
    cout << mod(dp[a][b][c][0] + mod(dp[a][b][c][1] + dp[a][b][c][2])) << "\n";
}
