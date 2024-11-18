#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n; cin >> n;
	vi use(2 * n);
	rep(i, 0, n){
		int a; cin >> a; a--; use[a] = true;
	}
	vi ans;
	rep(t, 0, 2){
		set<int> left;
		for(int i = 2 * n - 1; i >= 0; i--){
			if(use[i]) left.insert(i);
			else {
				auto it = left.upper_bound(i);
				if(it != end(left)) left.erase(it);
			}
		}
		ans.push_back(n - size(left));
		rep(i, 0, 2*n) use[i] = !use[i];
	}
	cout << n-ans[1] << " " << ans[0] << "\n";

	
	return 0;
}
