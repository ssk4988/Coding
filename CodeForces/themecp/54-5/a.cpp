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
        int n, d; cin >> n >> d;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        int mn = 2e9;
        vi idxs;
        int prv = 0;
        rep(i, 0, n){
            int v = a[i] - prv - 1;
            prv = a[i];
            if(v < mn){
                mn = v;
                idxs = vi{i};
            } else if(v == mn){
                idxs.pb(i);
            }
        }
        int ans = mn;
        auto test = [&](vi &x) -> int {
            vi diffs;
            int prv = 0;
            for(int i : x) {
                diffs.pb(i - prv - 1);
                prv = i;
            }
            int last = (d - prv);
            sort(all(diffs));
            return min(diffs[0], max((diffs.back()-1)/2, last-1));
        };
        if(sz(idxs) == 2 && idxs[0] == idxs[1] - 1) {
            a.erase(begin(a) + idxs[0]);
            ans = max(ans, test(a));
        } else if(sz(idxs) == 1) {
            {
                vi a2(a);
                a2.erase(begin(a2) + idxs[0]);
                ans = max(ans, test(a2));
            }
            if(idxs[0] > 0){
                a.erase(begin(a) + idxs[0]-1);
                ans = max(ans, test(a));
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
