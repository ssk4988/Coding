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
        ll sum = 0;
        int n, k; cin >> n >> k;
        vi a(n);
        int mn = 1e9, mx = -1e9;
        rep(i, 0, n){
            cin >> a[i];
            sum += a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }
        int mxfreq = 0;
        rep(i, 0, n) {
            if(a[i] == mx) {
                mxfreq++;
            }
        }
        if(mx-mn > k+1 || (mx-mn == k+1 && mxfreq > 1)) {
            cout << "Jerry\n";
        } else {
            cout << (sum % 2 == 1 ? "Tom" : "Jerry") << "\n";
        }
    }
    
    return 0;
}
