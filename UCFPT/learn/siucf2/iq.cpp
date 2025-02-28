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
        int n; cin >> n;
        set<int> trolls;
        map<int, vi> child;
        map<int, int> depth;
        trolls.insert(-5);
        depth[-5] = -1;
        rep(i, 0, n){
            int t; cin >> t;
            auto it = trolls.upper_bound(t);
            it--;
            int p = *it;
            depth[t] = depth[p]+1 + sz(child[p]);
            child[p].pb(t);
            trolls.insert(t);
            cout << depth[t] << "\n";
        }
    }
    
    return 0;
}
