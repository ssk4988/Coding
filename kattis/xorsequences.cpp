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

const int mod = 1e9+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int m, n; cin >> m >> n;
    int m2 = 1 << m;
    vvi used(m2, vi(m+1));

    vi a(m2);
    rep(i, 0, m2) cin >> a[i];
    auto dfs = [&](int lo, int hi, int bit, auto &&dfs) -> ll {
        rep(i, lo, hi) {
            if(used[i][bit]) return 0;
            used[i][bit] = 1;
        }
        if(hi-lo==1) {
            return 1;
        }
        int mid = lo + (hi-lo)/2;
        if(a[lo] == a[mid]) {
            bool eq = true;
            rep(i, 0, mid-lo) {
                if(a[lo+i] != a[mid+i]) eq = false;
            }
            if(!eq) return 0;
            return 2 * dfs(lo, mid, bit-1, dfs) % mod; // can set bit to 0 or 1
        }
        return dfs(lo, mid, bit-1, dfs) * dfs(mid, hi, bit-1, dfs) % mod;
    };
    ll ans = dfs(0, m2, m, dfs);
    cout << ans << "\n";
    
    return 0;
}
