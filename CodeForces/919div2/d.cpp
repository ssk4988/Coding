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
const ll LIM = 1e18+1e9;
ll add(ll a, ll b) {
    if(a >= LIM-b) return LIM;
    return a + b;
}
ll mult(ll a, ll b) {
    if(!a || !b) return 0;
    ll mxa = LIM / b;
    if(a >= mxa) return LIM;
    return a*b;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<vl> cs;
    cs.resize(1);
    // for each node, vector of prefix sum of sizes
    vector<vii> child; // {cid, cnt}
    vi isleaf; // -1 if not leaf, otherwise is val
    isleaf.pb(-1);
    child.resize(1);
    int root = 0;
    rep(i, 0, n) {
        int t, x; cin >> t >> x;
        ll cursize = sz(cs[root]) ? cs[root].back() : 0;
        if(cursize >= LIM) continue;
        if(t == 1) {
            cs[root].push_back(add(cursize,1));
            child[root].push_back({sz(cs), 1});
            cs.push_back({1});
            isleaf.push_back(x);
            child.push_back({});
        } else {
            x++;
            cs.push_back(vl{mult(cursize, x)});
            isleaf.push_back(-1);
            child.push_back({});
            child.back().push_back({root, x});
            root = sz(cs)-1;
        }
    }
    rep(i, 0, q) {
        ll k; cin >> k; k--;
        int cur = root;
        while(isleaf[cur] == -1) {
            int idx = upper_bound(all(cs[cur]), k) - begin(cs[cur]);
            assert(idx != sz(cs[cur]));
            // idx--;
            if(idx) k -= cs[cur][idx-1];
            k %= cs[child[cur][idx].f].back();
            cur = child[cur][idx].f;
        }
        cout << isleaf[cur] << " ";
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
