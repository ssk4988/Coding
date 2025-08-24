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
        vector<array<int, 3>> a(n);
        rep(i, 0, n) {
            cin >> a[i][0] >> a[i][1];
            a[i][1] *= -1;
            a[i][2] = i;
        }
        sort(all(a));
        int to = 0;
        vi res;
        for(auto [u, v, i] : a) {
            v *= -1;
            if(v <= to) continue;
            to = v;
            res.pb(i);
        }
        cout << sz(res) << "\n";
        for(auto i : res) cout << i+1 << " ";
        cout << "\n";
    }
    
    return 0;
}
