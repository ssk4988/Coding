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
const ll mod = 1e9+7;

struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = ssize(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod,
      inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl b(n+1);
        rep(i, 0, n) cin >> b[i+1];
        vi freq(29);
        int p = n;
        while(true) {
            while(p > 0 && b[p] == 0) p--;
            if(p == 0) break;
            rep(i, 0, 29) {
                if(b[p] & (1 << i)) {
                    freq[i] += p;
                }
            }
            rep(i, 1, p+1) {
                ll sub = C(p, i) * b[p] % mod;
                (b[i] -= sub) %= mod;
                (b[i] += mod) %= mod;
            }
        }
        vi a(n);
        rep(i, 0, n) {
            rep(j, 0, 29) if(freq[j]) {
                freq[j]--;
                a[i] |= 1 << j;
            }
        }
        rep(i, 0, n) cout << a[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
