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
        int n, m, q; cin >>n  >> m >> q;
        set<int> pos;
        rep(i, 0, m) {
            int v; cin >> v; v--;
            pos.insert(v);
        }
        rep(i, 0, q){
            int x; cin >> x;
            x--;
            if(x < *begin(pos)) {
                cout << *begin(pos) << "\n";
                continue;
            }
            if(x > *rbegin(pos)) {
                cout << (n-1 - *rbegin(pos)) << "\n";
                continue;
            }
            int l = *prev(pos.upper_bound(x));
            int r = *pos.upper_bound(x);
            cout << (r-l)/2 << "\n";
        }
    }
    
    return 0;
}
