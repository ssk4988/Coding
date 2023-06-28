#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl= vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vpl> adj(n);
    rep(i, 0, n - 1){
        ll a, b, w; cin >> a >> b >> w;
        a--,b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }    
    vector<vl> dp(n, vl(2));
    // 1: use edge to parent 0: don't use edge to parent
    auto dfs = [&](int cur, int par, ll paredge, auto &&dfs)->void{
        vpl branches;
        for(auto [nex, w] : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, w, dfs);
            dp[cur][0] += max(dp[nex][0], dp[nex][1]);
            branches.pb({w + dp[nex][0] - max(dp[nex][0], dp[nex][1]), nex});
        }
        sort(all(branches));
        reverse(all(branches));
        if(sz(branches) >= 2){
            ll c2 = branches[0].f + max(dp[branches[0].s][0], dp[branches[0].s][1]) + branches[1].f + max(dp[branches[1].s][0], dp[branches[1].s][1]);
            for(auto [nex, w] : adj[cur]){
                if(nex == par || nex == branches[0].s || nex == branches[1].s) continue;
                c2 += max(dp[nex][0], dp[nex][1]);
            }
            dp[cur][0] = max(dp[cur][0], c2);
        }
        if(sz(branches) >= 1 && par != -1){
            ll c1 = branches[0].f + max(dp[branches[0].s][0], dp[branches[0].s][1]) + paredge;
            for(auto [nex, w] : adj[cur]){
                if(nex == par || nex == branches[0].s) continue;
                c1 += max(dp[nex][0], dp[nex][1]);
            }
            dp[cur][1] = max(dp[cur][1], c1);
        }
    };
    dfs(0, -1, 0, dfs);
    cout << dp[0][0] << "\n";
}
