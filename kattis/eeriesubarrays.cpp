#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n; cin >> n;
	vi a(n);
	const int K = 500;
	int blocks = (n+K-1) / K;
	vvi freq(blocks, vi(2*K+1));
	vii ord;
	rep(i, 0, n) {
		cin >> a[i]; a[i]--;
		ord.push_back({a[i], i});
	}
	sort(all(ord));
	reverse(all(ord));
	vi val(n, -1);
	vi pref(blocks);
	auto upd = [&](int i, int x) {
		int b = i / K;
		val[i] = x;
		pref[b] = 0;
		fill(all(freq[b]), 0);
		rep(j, b*K, min((b+1)*K, n)) {
			pref[b] += val[j];
			freq[b][pref[b]+K]++;
		}
	};
	rep(i, 0, n) {
		upd(i, -1);
	}
	ll ans = 0;
	for(auto [x, i] : ord) {
		upd(i, 0);
		int cur = 0;
		int j = i;
		while(j < n && j % K != 0) {
			cur += val[j++];
			ans += cur == 0;
		}
		while(j < n) {
			if(abs(cur) <= K) ans += freq[j / K][K-cur];
			cur += pref[j / K];
			j += K;
		}
		upd(i, 1);
	}
	cout << ans << "\n";
	
	return 0;
}
