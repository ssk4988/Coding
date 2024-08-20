#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    set<int> s;
    s.insert(-1);
    s.insert(n);
    ll ans = 0;
    rep(i, 0, n){
        cin >> a[i];
        a[i]--;
        auto it = s.upper_bound(a[i]);
        int r = *it;
        int l = *prev(it);
        ans += r - l - 1;
        s.insert(a[i]);
    }
    cout << ans << "\n";

    return 0;
}