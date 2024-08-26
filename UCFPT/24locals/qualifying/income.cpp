#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a)); reverse(all(a));
    ld ans = 0;
    ll sum = accumulate(all(a), 0LL);
    ld cur = 0;
    for(int i = 0; i < n; i++) {
        cur += a[i];
        if(i + 1 >= n || a[i] != a[i+1]){
            ans = max(ans, cur / sum - (i+1) / ld(n));
        }
    }
    ans *= 100;
    cout << fixed << setprecision(8) << ans << "\n";

    return 0;
}
