#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c;
    cin >> r >> c;
    int sr, sc, er, ec;
    cin >> sr >> sc >> er >> ec;
    sr--, sc--, er--, ec--;
    vvi m(r, vi(c));
    rep(i, 0, r)
    {
        rep(j, 0, c)
        {
            cin >> m[i][j];
            m[i][j]--;
        }
    }
    vector<vvi> dp(r, vvi(c, vi(1 << 10)));
    // dp[sr][sc][1 << m[sr][sc]] = true;
    queue<array<int, 3>> q;
    q.push({sr, sc, 1 << m[sr][sc]});
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while(!q.empty()){
        auto [ir, ic, mask] = q.front(); q.pop();
        if(dp[ir][ic][mask]) continue;
        dp[ir][ic][mask] = true;
        rep(k, 0, 4){
            int jr = ir + ds[k][0], jc = ic + ds[k][1];
            if(jr < 0 || jc < 0 || jr >= r || jc >= c) continue;
            int newmask = mask | (1 << m[jr][jc]);
            if(!dp[jr][jc][newmask]){
                q.push({jr, jc, newmask});
            }
        }
    }
    int ans = 100;
    rep(i, 0, 1 << 10){
        if(dp[er][ec][i]){
            ans = min(ans, __builtin_popcount(i));
        }
    }
    cout << ans << "\n";
    return 0;
}
