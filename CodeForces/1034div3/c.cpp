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
        rep(i, 0, n) cin >> a[i];
        vi pref(a), suff(a);
        rep(i, 1, n) pref[i] = min(pref[i], pref[i-1]);
        for(int i = n-2; i >= 0; i--) suff[i] = max(suff[i], suff[i+1]);
        rep(i, 0, n) {
            if(a[i] == suff[0] || a[i] == pref[n-1] || (a[i] == pref[i]) || (a[i] == suff[i])) cout << "1";
            else cout << "0";
        }
        cout << "\n";
    }
    
    return 0;
}
