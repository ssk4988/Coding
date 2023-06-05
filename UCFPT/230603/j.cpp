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
using vvl = vector<vl>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl b(n);
    rep(i, 0, n){
        cin >> b[i];
    }
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, c; cin >> a >> c;
        a--,c--;
        adj[a].pb(c);
        adj[c].pb(a);
    }
    vvl dp(n, vl(2));
    auto solve = [&](int cur, int p, auto &&solve)->void{
        for(int i : adj[cur]){
            if(i == p) continue;
            solve(i, cur, solve);
        }
        priority_queue<ll> pq;
        ll curv = b[0];
        for(int i : adj[cur]){
            if(i == p) continue;
            curv += dp[i][1];
            pq.push(dp[i][0] - dp[i][1]);
        }
        int cnt = 0;
        dp[cur][0] = max(dp[cur][0], curv);
        if(p != -1)dp[cur][1] = max(dp[cur][1], curv + b[cnt + 1] - b[cnt]);
        while(!pq.empty()){
            ll dif = pq.top(); pq.pop();
            curv += dif;
            curv += b[cnt + 1] - b[cnt];
            cnt++;
            dp[cur][0] = max(dp[cur][0], curv);
            if(p != -1)dp[cur][1] = max(dp[cur][1], curv + b[cnt + 1] - b[cnt]);
        }
    };
    solve(0, -1, solve);
    cout << dp[0][0] << "\n";
    return 0;
}
