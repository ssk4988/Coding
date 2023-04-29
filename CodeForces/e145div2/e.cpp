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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, a, b; cin >> n >> a >> b;
    vi ops(n);
    rep(i, 0, n){
        cin >> ops[i];
    }
    vvi dp(a + 1, vi(b + 1));
    vector<vector<int>> ans(a + 1, vector<int>(b + 1));
	rep(cd, 0, a + b + 1){
		int l = max(0, cd - b), r = min(a, cd);
		int sum = 0;
		for (int x : ops){
			sum += x;
			l = max({l, sum, cd + sum - b});
			r = min({r, a + sum, sum + cd});
		}
		if (l > r) l = r = max(0, cd - b);
		int res = l;
		for (int x : ops){
			if (x > 0)
				res -= min({res, x, b - (cd - res)});
			else
				res += min({cd - res, -x, a - res});
		}
		rep(c, 0, cd + 1) if (c <= a && cd - c <= b){
			dp[c][cd - c] = (c < l ? res : (c > r ? res + r - l : res + c - l));
		}
	}
	rep(i, 0, a + 1){
		rep(j, 0, b + 1)
			cout << dp[i][j] << " ";
		cout << nL;
	}
    
    return 0;
}
