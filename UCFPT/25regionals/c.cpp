#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	
	int n, d, c; cin >> n >> d >> c;
	vi x(n);
	rep(i, 0, n) cin >> x[i];
	int lo = *ranges::partition_point(views::iota(0, d+1), [&](int cur) {
		int v = c, works = true;
		for(int a : x){
			v += a - cur;
			if(v < 0) { works = false; break; }
			v = clamp(v, 0, c);
		}
		return works;
	}) - 1;
	int hi = *ranges::partition_point(views::iota(0, d+1), [&](int cur) {
		int v = 0, works = true;
		for(int a : x) {
			v += a - cur;
			if(v > c) { works = false; break; }
			v = clamp(v, 0, c);
		}
		return !works;
	});
	cout << max(0, hi - lo) << "\n";
	
	return 0;
}
