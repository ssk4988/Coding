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

const int mod = 1e9+7; //!< must be prime
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
// CHECK ORIGINAL ALSO
void solve() {
    int n, m, q; cin >> n >> m >> q;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vii ops(q);
    vi freq(n);
    rep(i, 0, q) {
        cin >> ops[i].f >> ops[i].s;
        ops[i].f--;
        freq[ops[i].f]++;
    }
    grow(2*q+5);
    // does doing i then j have j be the last action if we are considering at
    auto interfere = [&](int at, int i, int j) -> bool {
        auto [pi, xi] = ops[i];
        auto [pj, xj] = ops[j];
        // assert(pi != at && pj != at);
        if(pj >= at && xi-pi >= xj-pj) return true;
        if(pj <= at && xi-pi <= xj-pj) return true;
        return false;
    };
    
    vi stop(q);
    rep(i, 0, q) {
        rep(j, 0, q) {
            if(ops[i].f == ops[j].f) continue;
            stop[i] += interfere(-1, i, j);
        }
    }
    rep(at, 0, n) {
        ll ans = 0;
        rep(i, 0, q) {
            if(ops[i].f != at) continue;
            rep(j, 0, q) {
                if(ops[i].f == ops[j].f) continue;
                stop[i] -= interfere(at-1, i, j);
                stop[i] += interfere(at, i, j);
                stop[j] -= interfere(at-1, j, i);
                stop[j] += interfere(at, j, i);
            }
            // cerr << "at=" << at << " i=" << i << " stop=";
            // rep(j, 0, q) cerr << stop[j] << " ";
            // cerr << endl;
        }
        rep(i, 0, q) {
            int inter = stop[i] + freq[ops[i].f];
            int target = 0;
            rep(j, 0, q) target += interfere(at, i, j);
            int place = ops[i].s-ops[i].f+at;
            if(ops[i].f > at) place = min(place, a[at]);
            if(ops[i].f < at) place = max(place, a[at]);
            ll ways = t[q].fact * t[inter-1].fact % mod * t[inter].inv_fact % mod;
            cerr << at << " " << i << " stop " << stop[i] << " inter " << inter << " target " << target << " place " << place << " " << ways << endl;
            // ll ways = t[inter-1].fact * C(q, inter) % mod * t[q-(inter)].fact % mod;
            (ans += place * ways) %= mod;
        }
        rep(i, 0, q) {
            rep(j, 0, q) cerr << interfere(at, i, j);
            cerr << endl;
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    
    return 0;
}
