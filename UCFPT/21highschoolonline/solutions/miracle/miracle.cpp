#include <bits/stdc++.h>
using namespace std;

void solve() {

    int n;
    cin >> n;

    double ans_log = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        ans_log += log((100 + x) / 100.0);
    }

    double ans = 100 * (exp(ans_log) - 1);

    cout << setprecision(8) << fixed << ans << "\n";
}

int main() {
	int t;
	cin >> t;
	while (t--)
		solve();
}
