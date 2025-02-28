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
        int n, q; cin >> n >> q;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        bool sw = false;
        vi pref(n+1);
        partial_sum(all(a), begin(pref)+1);
        rep(i, 0, q) {
            int t; cin >> t;
            if(t == 1) sw = !sw;
            else {
                int l, r; cin >> l >> r; l--;
                if(sw) {
                    r = n-r, l = n-l;
                    swap(l, r);
                }
                cout << pref[r]-pref[l] << "\n";
            }
        }
    }
    
    return 0;
}
