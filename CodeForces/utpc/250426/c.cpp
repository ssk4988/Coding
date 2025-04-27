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
    int n, q; cin >> n >> q;
    vi c;
    vii ints(n);
    rep(i, 0, n) {
        cin >> ints[i].f >> ints[i].s;
        ints[i].f--;
        c.pb(ints[i].f);
        c.pb(ints[i].s);
    }
    vi qs(q);
    rep(i, 0, q) {
        cin >> qs[i];
        qs[i]--;
        c.pb(qs[i]);
    }
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    rep(i, 0, n) {
        ints[i].f = lower_bound(all(c), ints[i].f) - begin(c);
        ints[i].s = lower_bound(all(c), ints[i].s) - begin(c);
    }
    rep(i, 0, q) {
        qs[i] = lower_bound(all(c), qs[i]) - begin(c);
    }
    vi pref(sz(c));
    rep(i, 0, n) {
        pref[ints[i].f]++;
        pref[ints[i].s]--;
    }
    rep(i, 1, sz(pref)){
        pref[i] += pref[i-1];
    }
    rep(i, 0, q) {
        cout << pref[qs[i]] << "\n";
    }
    
    return 0;
}
