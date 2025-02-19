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

const ll mod = 1e9 + 7;
struct comb
{
    int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n)
{
    for (int i = sz(t); i < n + 1; i++)
    {
        int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
        t.push_back({inv, i * t[i - 1].fact % mod,
                     inv * t[i - 1].inv_fact % mod});
    }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k)
{
    if (k < 0 || n < k)
        return 0;
    grow(n);
    return t[n].fact * t[k].inv_fact % mod *
           t[n - k].inv_fact % mod;
}

const int N = 300;


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    vector<vl> c(N, vl(N)); // C(i, j)
    rep(i, 0, N) {
        rep(j, 0, N) {
            c[i][j] = C(i, j);
        }
    }
    vector<vl> c_pre(c); // prefix sum on column
    rep(i, 1, N) {
        rep(j, 0, N) {
            (c_pre[i][j] += c_pre[i-1][j]) %= mod;
        }
    }
    rep(cn, 0, nc)
    {
        int n, c, m; cin >> n >> c >> m;
        vector<vl> dp(n, vl(m+1));
        dp[0][c] = 1;
        vi burn(m);
        rep(i, 0, m) cin >> burn[i];
        rep(i, 0, n-1) {
            rep(len, 0, sz(dp[i])) {
                rep(put, 0, c+1) {
                    int len1 = len + put;
                    if(len1 > m) continue;
                    if(put == 0) {
                        (dp[i+1][len] += dp[i][len]) %= mod;
                        continue;
                    }
                    int maxlast = c-put;
                    ll mult = c_pre[put-1+maxlast][put-1];
                    (dp[i+1][len1] += dp[i][len] * mult) %= mod;
                }
            }
        }
        cout << dp[n-1][m] << "\n";
    }

    return 0;
}
