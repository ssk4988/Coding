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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi child(n);
        rep(i, 1, n){
            int p; cin >> p;
            child[p].pb(i);
        }
        auto dfs = [&](int u, auto &&dfs) -> int {
            vi c;
            for(int v : child[u]) c.pb(dfs(v, dfs));
            sort(all(c));
            reverse(all(c));
            int ans = 0;
            rep(i, 0, sz(c)){
                ans = max(ans, c[i] + i + 1);
            }
            return ans;
        };
        cout << dfs(0, dfs) << "\n";
    }
    
    return 0;
}
