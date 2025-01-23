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

void solve() {
    int n; cin >> n;
    vii rng(n);
    vi cnt(2 * n + 10, 1);
    vi cover(2 * n + 10);
    rep(i, 0, n){
        cin >> rng[i].f >> rng[i].s;
        rng[i].f--;
        if(rng[i].f + 1 == rng[i].s) cnt[rng[i].f] = 0, cover[rng[i].f]++;
    }
    vi pref(cnt);
    rep(i, 1, sz(cnt)) pref[i] += pref[i-1];
    pref.insert(begin(pref), 0);
    rep(i, 0, n){
        int c = pref[rng[i].s] - pref[rng[i].f];
        if(rng[i].f + 1 == rng[i].s && cover[rng[i].f] == 1) c++;
        if(c) cout << 1;
        else cout << 0;
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
