#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n+1, vi(m+1));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            grid[i][j] = str[j] == '1';// + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
        }
    }
    int ans = 0;
    rep(i, 0, n){
        vi col(m);
        rep(j, i, n){
            rep(k, 0, m){
                col[k] += grid[j][k];
            }
            int curpref = 0;
            rep(k, 0, m){
                if(col[k] == j - i + 1) curpref += col[k];
                else curpref = 0;
                ans = max(ans, curpref);
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
