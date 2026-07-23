#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vi ans;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        set<int> s(all(a));
        int mx = 0;
        bool works = false;
        for(int i = n-1; i >= 0; i--) {
            s.erase(a[i]);
            auto it = s.upper_bound(a[i]);
            if(it != end(s) && mx > *it) {
                works = true;
            }
            mx = max(mx, a[i]);
        }
        if(works) ans.push_back(cn);
    }
    cout << sz(ans) << "\n";
    for(auto x : ans) cout << x+1 << "\n";

    return 0;
}
