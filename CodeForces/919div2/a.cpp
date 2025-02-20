#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int mn = INT_MIN, mx = INT_MAX;
        int n; cin >> n;
        set<int> bad;
        rep(i, 0, n) {
            int t; cin >> t; int x; cin >> x;
            if(t == 1) mn = max(mn, x);
            else if(t == 2) mx = min(mx, x);
            else bad.insert(x);
        }
        int ans = max(0, mx-mn+1);
        for(int x : bad) if(mn <= x && x <= mx) ans--;
        cout << ans << "\n";
    }
    
    return 0;
}
