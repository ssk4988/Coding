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
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vi c(a);
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    rep(i, 0, n) a[i] = lower_bound(all(c), a[i]) - begin(c);
    int ans = 0;
    vi above(sz(c));
    int prv = -2;
    rep(i, 0, n) {
        if(i && a[i] != prv) ans++;
        if(i && a[i] == prv+1) {
            above[prv] = 1;
        }
        prv = a[i];
    }

    rep(i, 0, sz(above)) if(above[i]) ans--;
    cout << ans << "\n";
    
    return 0;
}

// 1 | 2 3 | 1 | 2 | 1 2
// 1 | 2 3 | 0 1 | 2 | 1 2
