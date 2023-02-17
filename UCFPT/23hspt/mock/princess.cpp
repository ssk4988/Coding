#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<vi> vvi;
typedef pair<ll, pi> pp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int v, e;
    cin >> v >> e;
    vector<vector<pil>> adj(v);
    vvl dp(v, vl(2, LLONG_MAX));
    vvi visited(v, vi(2, 0));
    rep(i, 0, e){
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--, b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }
    dp[0][0] = 0;
    priority_queue<pp, vector<pp>, greater<pp>> pq;
    pq.push({0, {0, 0}});
    // cout << "pqd" << "\n";
    while(!pq.empty()){
        pp p = pq.top(); pq.pop();
        if(visited[p.s.f][p.s.s] != 0) continue;
        visited[p.s.f][p.s.s] = 1;
        if(p.s.s == 0){
            int nexv = v - 1 - p.s.f;
            if(dp[nexv][1] > dp[p.s.f][p.s.s] && visited[nexv][1] == 0){
                dp[nexv][1] = dp[p.s.f][p.s.s];
                pq.push({dp[nexv][1], {nexv, 1}});
            }
        }
        for(auto &pa : adj[p.s.f]){
            auto [nei, w] = pa;
            if(dp[nei][p.s.s] > dp[p.s.f][p.s.s] + w && visited[nei][p.s.s] == 0){
                dp[nei][p.s.s] = dp[p.s.f][p.s.s] + w;
                pq.push({dp[nei][p.s.s], {nei, p.s.s}});
            }
        }
    }
    vl ans(v);
    rep(i, 1, v){
        ans[i] = min(dp[i][0], dp[i][1]);
        if(ans[i] == LLONG_MAX){
            ans[i] = -1;
        }
        cout << ans[i];
        if(i + 1 < v){
            cout << " ";
        }
        else{
            cout << "\n";
        }
    }

}