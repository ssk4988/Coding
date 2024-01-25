#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

vi pi(const string& s){
    vi p(sz(s));
    rep(i, 1, sz(s)){
        int g= p[i-1];
        while(g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    // test n =1
    string str; cin >> str;
    vvi dp(n, vi(n));
    rep(j, 0, n){
        for(int i = j; i >= 0; i--) {
            int l = j - i + 1;
            dp[i][j] = l;
            vi p = pi(str.substr(i, l));
            if(l % (l - p.back()) == 0){
                dp[i][j] = min(dp[i][j], dp[i][i + l - p.back() - 1]);
                // if(p.back() != 0){
                //     cout << i << " " << j << " is rep with " << (l - p.back()) << "\n";
                // }
            }
            rep(k, i, j){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }
    cout << dp[0][n - 1] << "\n";

    return 0;
}
