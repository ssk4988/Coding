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
    int k, n; cin >> k >> n; n++, k++;
    vi sal(n), prod(n);
    vvi child(n);
    rep(i, 1, n) {
        cin >> sal[i] >> prod[i]; int par; cin >> par;
        child[par].push_back(i);
    }
    auto test = [&](ld r) -> bool {
        auto dfs = [&](int u, auto &&dfs) -> vd {
            vd res{0};
            for(int v : child[u]) {
                vd c = dfs(v, dfs);
                vd res1(sz(c)+sz(res)-1, -1e18);
                rep(i, 0, sz(res)) {
                    rep(j, 0, sz(c)) {
                        res1[i+j] = max(res1[i+j], res[i]+c[j]);
                    }
                }
                res = res1;
            }
            if(u) for(auto &x : res) x += prod[u] - r * sal[u];
            res.insert(begin(res), 0);
            return res;
        };
        vd res = dfs(0, dfs);
        return res[k] >= 0;
    };
    ld lo = 0, hi = 11000;
    rep(iter, 0, 50) {
        ld mid = (lo+hi)/2;
        if(test(mid)) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(3) << lo << endl;

    
    return 0;
}
