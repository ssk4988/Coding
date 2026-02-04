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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n);
    rep(i, 0 ,n) cin >> a[i];
    sort(all(a));
    reverse(all(a));
    ll above = 0, window = 0;
    int r = 0;
    vl pref(n+1);
    rep(i, 0, n) {
        while(r < n && (r <= i || above > window)) window += a[r++];
        above += a[i];
        window -= a[i];
        pref[i] += a[i];
        pref[r] -= 2 * a[i];
    }
    int ans = 0;
    rep(i, 0, n) {
        pref[i+1] += pref[i];
        if(pref[i] >= 0) {
            ans++;
        }
    }
    cout << ans << "\n";


    return 0;
}
