#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
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

const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}

vi pi(const string& s) {
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
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string str; cin >> str;
    int m = sz(str);
    vi kmp = pi(str);
    vvi aut(m + 1, vi(26));
    aut[0][str[0] - 'A'] = 1;
    rep(i, 1, m){
        aut[i][str[i] - 'A'] = i + 1;
        rep(j, 0, 26){
            if(aut[i][j] != 0) continue;
            aut[i][j] = aut[kmp[i - 1]][j];
        }
    }
    rep(i, 0, 26) aut[m][i] = m;
    vector<vl> dp(n + 1, vl(m + 1));
    dp[0][0] = 1;
    rep(i, 0, n){
        rep(j, 0, m + 1){
            rep(k, 0, 26){
                dp[i + 1][aut[j][k]] = mod(dp[i + 1][aut[j][k]] + dp[i][j]);
            }
        }
    }
    cout << dp[n][m] << nL;
    return 0;
}
