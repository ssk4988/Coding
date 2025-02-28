#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	int n, k; cin >> n >> k;
	vi a(n); rep(i, 0, n) cin >> a[i];
	vector dp(n+1, vi(n+1, 1e9));
	vector dp2(n+1, vector(n+1, vi(k+1, 1e9)));
	rep(l, 0, n+1) dp[l][l] = dp2[l][l][0] = 0;
	for(int l = n-1; l >= 0; l--) {
		rep(r, l+1, n+1) {
			rep(m, l+1, r+1) {
				dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r]);
				if (a[m-1] == a[l]) rep(v, 0, k+1)
					dp2[l][r][min(k, v+1)] = min(dp2[l][r][min(k, v+1)], dp2[l][m-1][v] + dp[m][r]);
			}
			rep(v, 0, k+1) dp[l][r] = min(dp[l][r], dp2[l][r][v] + k-v);
		}
	}
	cout << dp[0][n] << "\n";	
}
