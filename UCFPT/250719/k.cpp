#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        partial_sum(all(a), begin(a));
        a.insert(begin(a), 0);
        rep(i, 0, m) {
            int d1, m1, d2, m2; cin >> d1 >> m1 >> d2 >> m2;
            m1--, d1--, m2--, d2--;
            int v1 = d1 + a[m1], v2 = d2 + a[m2];
            int ans = v2 - v1;
            if(ans < 0) ans += a.back();
            ans++;
            cout << ans << "\n";
        }
    }
    
    return 0;
}
