#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;
using ld = long double;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; ld p; cin >> n >> k >> p;
    const int lim = 10000;
    vector<ld> cur(k+1);
    cur[k] = 1;
    ld ans = 0;
    rep(i, 1, lim+1) {
        vector<ld> nxt(k+1);
        rep(j, 1, k+1) {
            nxt[j] += cur[j] * p;
            nxt[j-1] += cur[j] * (1-p);
        }
        nxt[0] += cur[0];
        ld notover = pow(cur[0]+cur[1], n) - pow(cur[0], n);
        vector<ld> live(n);
        live[0] = 1;
        rep(_, 0, n-1) {
            for(int j = n-2; j >= 0; j--) {
                live[j+1] += live[j] * cur[1];
                live[j] *= cur[0];
            }
        }
        rep(otherlive, 1, n) {
            ans += n * (1 - nxt[0]) * live[otherlive] * pow(1-p, otherlive);
        }
        cur = nxt;
    }
    ans = 1 - ans;
    cout << fixed << setprecision(20) << ans << "\n";   

    return 0;
}
