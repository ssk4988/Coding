#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> s(n);
    rep(i, 0, n) cin >> s[i];
    const int inf = 1e9;
    vvi dp(n+1, vi(3, inf));
    dp[0][0] = 0;
    vector<char> vowels = {'A', 'E', 'I', 'O', 'U', 'Y'};
    rep(i, 0, n){
        rep(j, 0, 3){
            int run = j;
            rep(k, 0, min(3, sz(s[i]))){
                int con = find(all(vowels), s[i][k]) == vowels.end();
                run = con ? run + 1 : 0;
                if(run > 2) break;
                dp[i+1][run] = min(dp[i+1][run], dp[i][j] + k + 1);
            }
        }
    }
    int ans = *min_element(all(dp[n]));
    if(ans >= inf) cout << "*\n";
    else cout << ans << "\n";
    return 0;
}
