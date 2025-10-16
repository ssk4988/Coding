#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        vector<vpi> bits(2);
        int ans = 0;
        rep(i, 0, n) {
            cin >> grid[i];
            rep(j, 0, m) {
                if(grid[i][j] == '1') {
                    int r = i, c = (i+j)/2;
                    ans++;
                    bits[(i+j)&1].push_back({r-c, c});
                }
            }
        }
        rep(x, 0, 2) {
            sort(all(bits[x]));
            reverse(all(bits[x]));
            multiset<int> cs;
            for(auto [d, c] : bits[x]) {
                if(sz(cs)) {
                    auto it = cs.lower_bound(c);
                    if(it != end(cs)) {
                        cs.erase(*it);
                        ans--;
                    }
                }
                cs.insert(c);
            }
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
