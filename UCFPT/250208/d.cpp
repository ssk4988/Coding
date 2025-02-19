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
        int ans = 0;
        rep(i, 0, n) cin >> a[i];
        auto solve = [&](vi x) -> bool {
            while(true) {
                rep(i, 0, n) {
                    int nxt = i == n-1 ? 0 : i+1;
                    if(x[i]&1) {
                        x[i]--;
                        x[nxt] -= 2;
                    }
                }
                bool nonzero = false;
                rep(i, 0, n) {
                    if(x[i] < 0) return false;
                    x[i] >>= 1;
                    if(x[i]) nonzero = true;
                }
                if(!nonzero) break;
            }
            return true;
        };
        rep(rem, 0, 3) {
            int lo = -1;
            int hi = *max_element(all(a)) / 3 + 5;
            for(int dif = 1 << 28; dif; dif /= 2) {
                if(lo + dif >= hi) continue;
                vi x(a);
                rep(i, 0, n) x[i] -= (lo + dif) * 3;
                if(solve(x)) lo += dif;
            }
            vi x(a);
            rep(i, 0, n) x[i] -= lo * 3;
            if(solve(x)) ans = max(ans, rem + lo * 3);
            rep(i, 0, n) a[i]--;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
