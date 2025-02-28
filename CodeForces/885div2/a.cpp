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
        int n, m, k; cin >> n >> m >> k;
        int x, y; cin >> x >> y;
        int right = 0;
        rep(i, 0, k) {
            int x1, y1; cin >> x1 >> y1;
            if(((x1+y1)&1) == (x+y)&1) right++;
        }
        cout << (right<=0?"YES":"NO") << "\n";
    }
    
    return 0;
}
