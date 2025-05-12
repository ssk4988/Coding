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
    int n; cin >> n;
    vector<vl> a(2);
    rep(i, 0, n) {
        rep(j, 0, 2) {
            int b; cin >> b;
            a[j].push_back(b);
        }
    }
    __uint128_t ans = 0;
    rep(it, 0, 2) {
        sort(all(a[it]));
        rep(i, 0, sz(a[it])-1) {
            __uint128_t dx = a[it][i+1]-a[it][i];
            ans += dx * (i+1) * (n-(i+1));
        }
    }
    if(ans == 0) cout << 0 << "\n";
    else {
        vi digs;
        while(ans) {
            digs.pb(ans % 10);
            ans /= 10;
        }
        reverse(all(digs));
        for(int d : digs) cout << d;
        cout << "\n";
    }
    
    return 0;
}
