#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

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
    vll p(n);
    rep(i, 0, n){
        cin >> p[i].f >> p[i].s;
    }
    sort(all(p));
    vector<vll> buckets;
    for(auto [x, y] : p){
        if (sz(buckets) == 0 || buckets.back()[0].f != x) buckets.pb({});
        buckets.back().pb({x, y});
    }
    const ll inf = 1e18;
    auto check = [&](int k) -> pll {
        if(k == 0) return {0, 0};
        if(4 * k > n) return {inf, inf};
        int t = 0;

        Tree<pll> lowtree, hightree;
        for(auto &b : buckets){
            for(auto [x, y] : b) {
                hightree.insert({y, t++});
            }
        }
        t = 0;
        for(auto &b : buckets){
            for(auto [x, y] : b) {
                hightree.erase({y, t});
                lowtree.insert({y, t++});
            }
            if(min(t, n - t) < 2 * k) continue;
            pll lowl = *lowtree.find_by_order(k-1), lowr = *lowtree.find_by_order(t - k);
            pll highl = *hightree.find_by_order(k-1), highr = *hightree.find_by_order((n-t)-k);
            if(lowr.f <= highl.f || highr.f <= lowl.f || lowl.f == lowr.f || highl.f == highr.f) continue;

            return {b[0].f, max(lowl.f, highl.f)};
        }
        return {inf, inf};
    };
    int ans = 0;
    for(int dif = 1 << 20; dif; dif /= 2){
        auto [x,y] = check(ans + dif);
        if(x != inf) ans += dif;
    }
    auto [x,y] = check(ans);
    cout << ans << "\n" << x+1 << " " << y+1 << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
