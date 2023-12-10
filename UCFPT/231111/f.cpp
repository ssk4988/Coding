#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int dp[101][101][101];
pii pre[101][101][101];

int solve(int p, int q, int r) {
    if(dp[p][q][r] != -1) return dp[p][q][r];
    int &ans = dp[p][q][r];
    ans = 0; // losing
    rep(i, 1, p + 1){
        int res = !solve(i - 1, min(i - 1, q), min(i - 1, r));
        if(res > ans){
            ans = res;
            pre[p][q][r] = {i, 1};
        }
    }
    rep(i, 1, q + 1){
        int res = !solve(p, i - 1, min(i - 1, r));
        if(res > ans){
            ans = res;
            pre[p][q][r] = {i, 2};
        }
    }
    rep(i, 1, r + 1){
        int res = !solve(p, q, i - 1);
        if(res > ans){
            ans = res;
            pre[p][q][r] = {i, 3};
        }
    }
    // if(ans == 1){
    //     cout << p << " " << q << " " << r << " is wining\n";
    // }
    return ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // vector<vvi> dp(101, vvi(101, vi(101, -1)));
    memset(dp, -1, sizeof dp);
    dp[0][0][0] = 1; // winning state
    int nc; cin >> nc;
    rep(i, 0, nc){
        int cn, p, q, r; cin >> cn >> p >> q >> r;
        int ans = solve(p, q, r);
        if(ans == 0){
            cout << cn << " L\n";
        }
        else{
            cout << cn << " W " << pre[p][q][r].first << " " << pre[p][q][r].second << "\n";
        }
    }
    return 0;
}
