#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pi = pair<int, int>;

const bool DEBUG = false;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vvl dp(n, vl(2));
    ll ans = 0;
    auto dfs = [&](int cur, int par, auto &&dfs)->void{
        dp[cur][0] = 1;
        ll c = 0;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, dfs);
            swap(dp[nex][0], dp[nex][1]);
            rep(i, 0, 2){
                ans += dp[cur][i] * dp[nex][i];
                c += dp[cur][i] * dp[nex][i];
                dp[cur][i] += dp[nex][i];
            }
        }
        if(DEBUG)
            cout << "Node " << cur << " contributed " << c << ", dp[" << cur << "][0]=" << dp[cur][0] << ", dp[" << cur << "][1]=" << dp[cur][1] << "\n";
    };
    dfs(0, -1, dfs);
    ans *= 2;
    cout << ans << "\n";
}
