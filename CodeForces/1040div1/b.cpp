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
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i]; a[i]--;
        }
        vi flip(n);
        rep(i, 0, n) {
            int delta = 0;
            rep(j, 0, n) {
                if(i == j) continue;
                if(j < i && a[j] > a[i]) delta++;
                if(j > i && a[j] > a[i]) delta--;
            }
            if(delta > 0) {
                flip[i] = 1;
            }
        }
        rep(i, 0, n) if(flip[i]) a[i] = 2 * n - 1 - a[i];
        int inv = 0;
        rep(i, 0, n) {
            rep(j, 0, i) if(a[j] > a[i]) inv++;
        }
        cout << inv << "\n";
    }
    
    return 0;
}
