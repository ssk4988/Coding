#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n) {
        cin >> a[i];
        if(i) a[i] = min(a[i], 2*a[i-1]);
    }
    while(sz(a) < 35) {
        a.push_back(a.back() * 2);
    }
    rep(qid, 0, q) {
        ll x; cin >> x;
        ll ans = 0;
        ll ans2 = LLONG_MAX;
        for(int i = min(30, sz(a)-1); i >= 0; i--) {
            if((x >> i) & 1) {
                ans += a[i];
            }
            if((1LL << i) >= x) ans2 = min(ans2, a[i]);
        }
        cout << min(ans2,ans) << "\n";
    }

    return 0;
}
