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
    int n, m; cin >> n >> m;
    int edges = 2 * n * m;
    rep(mask, 0, 1 << edges){
        vi used(2 * n + m);
        auto dfs = [&](int u, int prv, int color, auto &&dfs) -> bool {
            if(used[u]) 
                return true;
            used[u] = true;
            if(u < 2 * n) {
                rep(i, 0, m){
                    if(i == prv) continue;
                    int c = u * m + i;
                    if(((mask >> c) & 1) != color) continue;
                    // int last = used[i + 2 * n];
                    // used[i + 2 * n] = true;
                    if(dfs(2 * n + i, u, color, dfs)) return true;
                    // used[i + 2 * n] = last;
                }
            } else {
                u -= 2 * n;
                rep(i, 0, 2 * n){
                    if(i == prv) continue;
                    int c = i * m + u;
                    if(((mask >> c) & 1) != color) continue;
                    // int last = used[i];
                    // used[i] = true;
                    if(dfs(i, u, color, dfs)) return true;
                    // used[i] = last;
                }
                u += 2 * n;
            }
            used[u] = false;
            return false;
        };
        bool works = true;
        rep(i, 0, 2 * n){
            used[i] = true;
            rep(j, 0, m){
                int c = i * m + j;
                if(dfs(2 * n + j, i, (mask >> c) & 1, dfs)){
                    works = false;
                    goto bad;
                }
            }
            used[i] = false;
        }
        bad:
        if(works){
            cout << mask << " " << bitset<12>(mask) << "\n";
        }
    }
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
