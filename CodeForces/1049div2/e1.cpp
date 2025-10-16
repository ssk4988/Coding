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



// bitmask of left guys, length
// for each bitmask of length n, get ans (1 if can end on 1), then for thresh (<= thresh is 0) the ways is (thresh)^0s * (m-thresh)^1s
const ll mod = 1e9+7;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vvi dp(n+1);
        int k; cin >> k;
        vi good(n);
        rep(i, 0, k) {
            int v; cin >> v; v--;
            good[v] = 1;
        }
        rep(i, 0, n+1) {
            dp[i] = vi(1 << i);
        }
        dp[1][0] = 0;
        dp[1][1] = 1;
        vi suffmask(n);
        suffmask[0] = (1 << n)-2;
        rep(i, 1, n) {
            suffmask[i] = suffmask[i-1] - (1 << i);
        }
        rep(i, 2, n+1) {
            int mx = (n-i) % 2 == 0;
            int allmask = (1 << (i-1))-1;
            rep(mask, 0, 1 << i) {
                dp[i][mask] = mx ? 0 : 1;
                rep(j, 0, i) {
                    if(!good[j]) continue;
                    int newmask = mask & ((1 << j)-1);
                    newmask |= (mask & suffmask[j])>>1;
                    newmask &= allmask;
                    // int newmask = mask & (((1 << j)-1) | suffmask[j]) & allmask;
                    int val = dp[i-1][newmask];
                    // cerr << mask << " " << i << " " << j << " " << newmask << " " << val << endl;
                    if(mx) dp[i][mask] = max(dp[i][mask], val);
                    else dp[i][mask] = min(dp[i][mask], val);
                }
            }
        }
        vl freq0(n+1);
        rep(mask, 0, 1 << n) {
            int pop0 = __builtin_popcount(mask);
            // cerr << "dp " << n << " " << mask << " " << dp[n][mask] << endl;
            if(dp[n][mask])
                freq0[pop0]++;
        }
        ll ans = 0;
        rep(thresh, 0, m+1) {
            vl t1(n+1);
            t1[0] = 1;
            rep(i, 1, n+1){
                t1[i] = t1[i-1] * (m-thresh) % mod;
            }
            ll t0 = 1;
            rep(c0, 0, n+1) {
                int c1 = n-c0;
                (ans += freq0[c0] * t0 % mod * t1[c1]) %= mod;
                (t0 *= thresh) %= mod;
            }
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
