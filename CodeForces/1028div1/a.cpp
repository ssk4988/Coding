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
        const int N = 5005;
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        vi make(N, 1e9);
        int tot = a[0];
        rep(i, 0, n) {
            tot = __gcd(tot, a[i]);
            vi make2(make);
            make2[a[i]] = min(make2[a[i]], 0);
            for(int v = N-1; v >= 1; v--) {
                
                
                int t = __gcd(v, a[i]);
                make2[t] = min(make2[t], 1 + make[v]);
            }
            make = make2;
        }
        int cost = make[tot];
        if(cost) cost--;
        rep(i, 0, n) {
            if(a[i] != tot) cost++;
        }
        cout << cost << "\n";
    }
    
    return 0;
}
