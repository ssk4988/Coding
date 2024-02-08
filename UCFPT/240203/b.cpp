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
    const int LIM = 1e6 + 1;
    int n; cin >> n;
    vvi adj(n), bucket(LIM);
    vi e(n);
    rep(i, 0, n){
        int d; cin >> e[i] >> d;
        bucket[e[i]].pb(i);
        rep(j, 0, d){
            int x; cin >> x; x--;
            adj[i].pb(x);
        }
    }
    int seen = 0, ans = 0;
    vi used(n);
    auto revdfs = [&](int u, auto &&self) -> void {
        if(used[u]) return;
        for(int v : adj[u]) self(v, self);
        used[u] = true;
        ans = max(seen++ + e[u], ans);
    };
    for(int i = sz(bucket) - 1; i >= 0; i--){
        for(auto x : bucket[i]){
            revdfs(x, revdfs);
        }
    }
    cout << ans << "\n";
    return 0;
}
