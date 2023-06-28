#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;

ll MOD = 998244353;
ll mod(ll k){
    return k % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n), child(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b; a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        auto dfs = [&](int cur, int p, auto &&dfs)->void{
            for(int i : adj[cur]){
                if(i == p) continue;
                child[cur].pb(i);
                dfs(i, cur, dfs);
            }
        };
        dfs(0, -1, dfs);
        vvl dp(n, vl(3, 1));
        auto calc = [&](int cur, auto &&calc)->void{
            if(sz(child[cur]) == 0){
                dp[cur] = {1, 0, 1};
                return;
            }
            for(int i : child[cur]){
                calc(i, calc);
                dp[cur][2] = mod(dp[cur][2] * dp[i][0]);
                dp[cur][0] = mod(dp[cur][0] * mod(dp[i][0] + dp[i][1]));
            }
            for(int i : child[cur]){
                dp[cur][1] = mod(dp[cur][1] * mod(dp[i][0] + dp[i][1] + dp[i][2]));
            }
            dp[cur][1] -= dp[cur][2];
            while(dp[cur][1] < 0) dp[cur][1] += MOD;
        };
        calc(0, calc);
        cout << mod(dp[0][0] + dp[0][1]) << "\n";
    }
}
