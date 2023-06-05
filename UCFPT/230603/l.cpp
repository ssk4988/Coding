#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, x; cin >> n >> x;x--;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi marked(n);
    auto dfs1 = [&](int cur, int p, auto &&dfs1)->bool{
        if(cur == x){
            marked[cur] = true;
            return true;
        }
        for(int i : adj[cur]){
            if(i == p) continue;
            if(dfs1(i, cur, dfs1)){
                marked[cur] = true;
            }
        }
        return marked[cur];
    };
    dfs1(0, -1, dfs1);
    vl dp(n);
    auto dfs = [&](int cur, int p, auto &&dfs)->ll{
        // if()
        // base case
        dp[cur] = 1;
        if(cur == x) return dp[cur];
        for(int i : adj[cur]){
            if(i == p )continue;
            if(i == x){
                dp[cur] += dfs(i, cur, dfs);
                return dp[cur];
            }
        }
        for(int i : adj[cur]){
            if(i == p) continue;
            dp[cur] += (!marked[i]) + dfs(i, cur, dfs);
        }
        return dp[cur];
    };
    cout << (dfs(0, -1, dfs) - 1) << "\n";
    return 0;
}
