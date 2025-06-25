#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vi d(n);
        rep(i, 0, n) cin >> d[i];
        sort(all(d));


        auto test = [&](int lasts) -> pair<bool, int> {
            int l = 0, r = n - 1 - lasts;
            int groups = 0;
            // cerr << "testing " << lasts << " ";
            while(l < r) {
                while(l < r && d[l] + d[r] >= k) {
                    if(d[r] < k) groups++;
                    else lasts++;
                    r--;
                }
                if(l < r && d[l] + d[r] < k) {
                    l++, r--;
                    groups++;
                }
            }
            if(l == r) {
                if(d[l] < k) groups++;
                else lasts++;
            }
            // cerr << (groups >= lasts) << " " << max(groups, lasts) << endl;
            return {groups >= lasts, max(groups, lasts)};
        };
        int lo = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            int cur = lo + dif;
            if(cur > n) continue;
            auto [lt, amt] = test(cur);
            if(lt) lo = cur;
        }
        int ans = n;
        rep(v, max(0, lo), 1+min(n, lo+5)) {
            ans = min(ans, test(v).second);
        }
        cout << ans-1 << "\n";
    }

    return 0;
}
