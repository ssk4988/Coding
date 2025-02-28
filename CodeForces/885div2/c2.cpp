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
        
        vi a(n), b(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        rep(i, 0, n) cin >> b[i];
        bool dull = false;
        vvi hist;
        hist.pb(a);
        hist.pb(b);
        rep(t, 0, 100) {
            vi c(n);
            rep(i, 0, n) c[i] = abs(hist[sz(hist)-2][i]-hist.back()[i]);
            hist.pb(c);
            if(accumulate(all(a), 0) == 0) 
                dull = true;
            rep(i, 0, n){
                cout << hist.back()[i] << " ";
            }
            cout << "\n";
        }
        cout << (!dull ?"NO":"YES") << "\n";
    }
    
    return 0;
}
