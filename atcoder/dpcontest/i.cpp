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

const ll mod = 998244353; //!< must be prime
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = sz(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod, inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod * t[n - k].inv_fact % mod;
}
ll sb(int alloc, int vars) {
    return C(alloc + vars - 1, alloc);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, L, R; cin >> n >> L >> R;
    vi freq(n);
    int mx = 0;
    rep(i, 0, n) {
        int a; cin >> a; a--;
        freq[a]++;
        mx = max(mx, a);
    }
    vi sufffreq(freq);
    for(int i = n-2; i >= 0; i--) {
        sufffreq[i] += sufffreq[i+1];
    }
    vector dp(n+1, vector(n+1, vl(n+1, -1)));
    auto go = [&](int i, int l, int r, auto &&go) -> ll {
        if(l <= 0 || r <= 0) return 0;
        if(i == mx) {
            // base case
            if(l != 1 || r != 1) return 0;
            return 1;
        }
        auto &ans = dp[i][l][r];
        if(ans != -1) return ans;
        ans = 0;
        if(freq[i] >= 0) {
            int space = sufffreq[i] - freq[i] - 1;
            (ans += go(i+1, l, r, go) * sb(freq[i], space)) %= mod;
        }
        if(freq[i] >= 1) {
            int space = sufffreq[i] - freq[i] - 1 + 1;
            (ans += go(i+1, l-1, r, go) * sb(freq[i]-1, space)) %= mod;
            (ans += go(i+1, l, r-1, go) * sb(freq[i]-1, space)) %= mod;
        }
        if(freq[i] >= 2) {
            int space = sufffreq[i] - freq[i] - 1 + 2;
            (ans += go(i+1, l-1, r-1, go) * sb(freq[i]-2, space)) %= mod;
        }
        return ans;
    };
    cout << go(0, L, R, go) << "\n";
    // vector dp(n+1, vl(n+1));
    // dp[0][0] = 1;
    // rep(i, 0, n) {
    //     vector nxt(n+1, vl(n+1));
    //     rep(j, 0, n) {
    //         rep(k, 0, n) {
    //             if(freq[i] == 0) {
    //                 (nxt[j][k] += dp[j][k]) %= mod;
    //             } else {
    //                 if(i != mx) {
    //                     (nxt[j+1][k] += dp[j][k]) %= mod;
    //                     (nxt[j][k+1] += dp[j][k]) %= mod;
    //                     if(freq[i] >= 2) (nxt[j+1][k+1] += (freq[i]-2) * dp[j][k]) %= mod;
    //                 } else {
    //                     (nxt[j+1][k+1] += dp[j][k]) %= mod;
    //                 }
    //             }
    //         }
    //     }
    //     rep(j, 0, n+1) {
    //         rep(k, 0, n+1) {
    //             cerr << i << " " << j << " " << k << " " << dp[j][k] << "\n";
    //         }
    //     }
    //     dp = nxt;
    // }
    // cout << dp[l][r] << "\n";
    
    return 0;
}
