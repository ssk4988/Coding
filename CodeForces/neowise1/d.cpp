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
        map<int, int> x, xy;
        rep(i, 0, n) {
            int a, b; cin >> a >> b;
            x[a]++;
            xy[a+b]++;
        }
        int tx, txy;
        for(auto [key, val] : x) if(val&1) tx = key;
        for(auto [key, val] : xy) if(val&1) txy = key;
        int ty = txy - tx;
        cout << tx << " " << ty << "\n";
    }
    
    return 0;
}
