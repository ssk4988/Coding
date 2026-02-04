#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using ld = long double;
const int N = 5010;
ld dp[N][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    dp[0][0] = dp[1][1] = dp[1][0] = 1;
    rep(i, 2, n+1) {
        rep(j, 0, i+1) {
            if(j == 0 || j == i) {
                dp[i][j] = 1;
                continue;
            }
            dp[i][j] = dp[i][j-1] / double(j) * (i-(j-1));
        }
    }
    // rep(i, 0, n+1) {
    //     rep(j, 0, i+1) {
    //         cerr << "C " << i << " " << j << " " << dp[i][j] << "\n";
    //     }
    // }
    auto C = [&](int n, int k) -> ld {
        if(n < 0 || k < 0 || k > n) return 0;
        return dp[n][k];
    };
    vector<ld> x(n), y(n);
    rep(i, 0, n) cin >> x[i] >> y[i];
    reverse(all(x)), reverse(all(y));
    auto cross = [&](int i, int j) -> ld {
        return x[i] * y[j] - x[j] * y[i];
    };
    ld tot = 0;
    {
        ld area = 0;
        rep(i, 0, n) {
            area += cross(i, (i+1)%n);
        }
        area /= 2;
        tot = area;
    }
    rep(l, 0, n) {
        ld shoelace = 0;
        int other = n-2;
        for(int r = (l+1)%n; r != l; r = (r+1)%n, other--) {
            shoelace += cross((r+n-1)%n, r);
            ld area = (shoelace + cross(r, l)) / 2;
            tot -= area * C(other, k-2) / C(n, k);
        }
    }
    cout << fixed << setprecision(20) << tot << "\n";

    return 0;
}
