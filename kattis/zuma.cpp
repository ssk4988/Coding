#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n, k; cin >> n >> k;
	vi a(n); rep(i, 0, n) cin >> a[i];
	vvi dp(n+1, vi(n+1, 1e9));
	vector dp_part(n+1, vector(n+1, vi(k+1, 1e9)));
	rep(l, 0, n+1) dp[l][l] = dp_part[l][l][0] = 0;
	for(int l = n-1; l >= 0; l--) {
		rep(r, l+1, n+1) {
			rep(m, l+1, r+1) {
				dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r]);
				if (a[m-1] == a[l]) rep(v, 0, k+1)
					dp_part[l][r][min(k, v+1)] = min(dp_part[l][r][min(k, v+1)], dp_part[l][m-1][v] + dp[m][r]);
			}
			rep(v, 0, k+1) dp[l][r] = min(dp[l][r], dp_part[l][r][v] + k-v);
		}
	}
	cout << dp[0][n] << "\n";
	
	return 0;
}
