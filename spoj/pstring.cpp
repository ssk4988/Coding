#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

vi kmp(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string x, y;
    while(cin >> x >> y){
        int n = sz(x), m = sz(y);
        vi p = kmp(y);
        // for(int i : p){
        //     cout << i << " ";
        // }
        // cout << endl;
        vvi aut(m, vi(26));
        rep(i, 0, m){
            if(i)
                aut[i] = aut[p[i-1]];
            aut[i][y[i]-'a'] = i+1;
        }
        // vvi dp(n + 1, vi(m+1, 1e9));
        vi prevdp(m+1, 1e9), dp(m+1, 1e9);
        dp[0] = 0;
        rep(i, 0, n){
            prevdp = dp;
            dp = vi(m+1, 1e9);
            rep(j, 0, m){
                dp[j] = min(dp[j], prevdp[j]+1);
                // cout << i << " " << j << " " << aut[j][x[i]-'a'] << endl;
                dp[aut[j][x[i]-'a']] = min(dp[aut[j][x[i] - 'a']], prevdp[j]);
            }
        }
        // cout << "dp:\n";
        // rep(i, 0, n+1){
        //     rep(j, 0, m + 1){
        //         cout << i << " " << j << " " << dp[i][j] << endl;
        //     }
        // }
        int ans = n;
        rep(i, 0, m) ans = min(ans, dp[i]);
        cout << ans << "\n";
    }
    
    return 0;
}
