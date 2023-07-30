#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    freopen("jenga.in", "r", stdin);
    // int BLANK = -1;
    // vector<vector<vector<int>>> dp(300, vector<vector<int>>(300, vi(300, BLANK)));
    // rep(i, 0, sz(dp)) dp[i][0][0] = 0;
    // auto solve = [&](int moves, int twos, int ones, auto &&solve)->int{
    //     if(dp[moves][twos][ones] != BLANK) return dp[moves][twos][ones];
    //     dp[moves][twos][ones] = 0;
    //     if(twos > 0){
    //         dp[moves][twos][ones] |= !solve(moves + 1, twos - 1 + ((moves+1)%3 == 0), ones, solve);
    //         dp[moves][twos][ones] |= !solve(moves + 1, twos - 1 + ((moves+1)%3 == 0), ones + 1, solve);
    //     }
    //     if(ones > 0){
    //         dp[moves][twos][ones] |= !solve(moves + 1, twos + ((moves+1)%3 == 0), ones - 1, solve);
    //     }
    //     return dp[moves][twos][ones];
    // };
    // rep(i, 1, 20){
    //     cout << i << ": " << (solve(0, i - 1, 0, solve) ? "Bakkar" : "Wahdan") << "\n";
    //     // cout << i << ": " << (((i - 1) / 2) % 2 == 0 ? "Bakkar" : "Wahdan") << "\n";
    // }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        cout << "Case " << (cn + 1) << ": " << (n % 3 != 0 ? "Bakkar" : "Wahdan") << "\n";
    }
}
