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

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi nex(n);
    vvi pre(n);
    rep(i, 0, n){
        cin >> nex[i];
        nex[i]--;
        pre[nex[i]].pb(i);
    }
    vi status(n);
    int numcycles = 0;
    vi cyclenum(n, -1);
    vi cyclelen;
    vi visited(n);
    vvi cycles(numcycles);
    auto dfs = [&](int cur, auto &&dfs)->void{
        if(visited[cur]) return;
        visited[cur] = true;
        for(int i : pre[cur]){
            dfs(i, dfs);
        }
    };
    rep(i, 0, n){
        if(visited[i]) continue;
        int a = nex[i], b = nex[nex[i]];
        while(a != b){
            a = nex[a];
            b = nex[nex[b]];
        }
        a = i;
        while(a != b){
            a = nex[a];
            b = nex[b];
        }
        int start = a;
        b = nex[a];
        int len = 1;
        while(b != a){
            b = nex[b];
            len++;
        }
        cyclenum[start] = numcycles;
        cycles.pb({});
        cycles.back().pb(start);
        for(b = nex[start]; b != start; b = nex[b]) {
            cyclenum[b] = numcycles;
            cycles.back().pb(b);
        }
        numcycles++;
        cyclelen.pb(len);
        dfs(start, dfs);
    }
    
    vvi dp(n, {0, 1});
    auto calc = [&](int cur, auto &&calc)->void{
        for(int i : pre[cur]){
            if(cyclenum[i] != -1) continue;
            calc(i, calc);
            dp[cur][0] += max(dp[i][0], dp[i][1]);
            dp[cur][1] += dp[i][0];
        }
    };

    rep(i, 0, n){
        if(cyclenum[i] != -1) {
            calc(i, calc);
        }
    }
    ll ans = 0;
    rep(c, 0, numcycles){
        reverse(all(cycles[c]));
        vector<vvi> dp2(sz(cycles[c]), vvi(2, vi(2)));
        // part of cycle, used first, used this
        // dp2[0][0][0] = dp[cycles[c][0]][0];
        // dp2[0][1][1] = dp[cycles[c][0]][1];
        // dp2[1][0][0] = dp[cycles[c][0]][0] + dp[cycles[c][1]][0];
        rep(i, 0, 2){
            rep(j, 0, 2){
                dp2[1][i][j] = dp[cycles[c][0]][i] + dp[cycles[c][1]][j];
            }
        }
        dp2[1][1][1] = -n - 100;
        rep(i, 2, sz(dp2)){
            dp2[i] = {{dp[cycles[c][i]][0], dp[cycles[c][i]][1]}, {dp[cycles[c][i]][0], dp[cycles[c][i]][1]}};
            rep(j, 0, 2){
                dp2[i][j][0] += max(dp2[i - 1][j][1], dp2[i - 1][j][0]);
                dp2[i][j][1] += dp2[i - 1][j][0];
            }
        }
        // if(sz(cycles[c]) % 2 == 1){
        ans += max(max(dp2.back()[0][0], dp2.back()[0][1]), dp2.back()[1][0]);
        // }
        // else{

        // }
    }
    cout << ans << "\n";
}
