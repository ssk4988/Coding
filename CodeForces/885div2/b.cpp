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
        int n, k; cin >> n >> k;
        vvi buckets(k, vi{0});
        rep(i, 0, n) {
            int a; cin >> a; a--; buckets[a].pb(i+1);
        }
        rep(i, 0, k) buckets[i].pb(n+1);
        int ans = n+5;
        rep(i, 0, k) {
            vi diffs;
            rep(j, 1, sz(buckets[i])) {
                diffs.pb(buckets[i][j]-buckets[i][j-1]);
            }
            sort(all(diffs));
            ans = min(ans, max((diffs.back()+1)/2, sz(diffs) >= 2 ? diffs[sz(diffs)-2]:0));
        }
        cout << ans-1 << "\n";
    }
    
    return 0;
}
