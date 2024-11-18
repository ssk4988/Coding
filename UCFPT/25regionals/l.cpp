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
    int n, m; cin >> n >> m;
    vii a(n, {-1, -1});
    rep(i, 0, n) cin >> a[i].s;
    vector<string> dyn = {"ppp", "pp", "p", "mp", "mf", "f", "ff", "fff"};
    rep(i, 0, m){
        int j; cin >> j; j--;
        string d; cin >> d;
        a[j].f = find(all(dyn), d) - begin(dyn);
    }
    rep(i, 0, n) {
        if(a[i].f == -1) a[i].f = a[i-1].f;
    }
    rep(i, 0, n) swap(a[i].f, a[i].s);
    ll ans = 0;
    vi cnt(8);
    sort(all(a));
    map<pii, int> frq;
    rep(i, 0, n) {
        rep(j, a[i].s+1, 8) ans += cnt[j];
        rep(j, 0, a[i].s) ans += frq[{a[i].f, j}];
        cnt[a[i].s]++;
        frq[a[i]]++;
    }
    cout << ans << "\n";
    return 0;
}
