#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int r, c; cin >> r >> c;
        vvi grid(r, vi(c));
        pi pac, e;
        string str; cin >> str;
        rep(i, 0, r){
            rep(j, 0, c){
                if(i == 0 && j == 0) continue;
                if(i == r - 1 && j == c - 1) continue;
                int k; cin >> k;
                grid[i][j] = k;
            }
        }
        cin >> str;
        vvi dp(r, vi(c));
        rep(i, 0, r){
            rep(j, 0, c){
                if(i + 1 < r){
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + grid[i + 1][j]);
                }
                if(j + 1 < c){
                    dp[i][j+1] = max(dp[i][j+1], dp[i][j] + grid[i][j+1]);
                }
            }
        }
        cout << dp[r - 1][c- 1] << "\n";
    }

    return 0;
}