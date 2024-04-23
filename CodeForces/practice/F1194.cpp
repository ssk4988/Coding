#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const ll MOD = 1e9+7; /**< must be prime */
const ll inv2 = (MOD + 1) / 2;
vector<int64_t> inv(2, 1), fact(inv), inv_fact(inv);
void grow(int n) {
  assert(n < MOD);
  while ((int)(inv).size() <= n) {
    int i = (int)(inv).size();
    inv.push_back(MOD - (MOD / i) * inv[MOD % i] % MOD);
    fact.push_back(i * fact[i - 1] % MOD);
    inv_fact.push_back(inv[i] * inv_fact[i - 1] % MOD);
  }
}
/**
 * @param n,k integers with n < MOD
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
inline int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll T; cin >> T;
    vl t(n);
    vl p2 = {1};
    rep(i, 0, n){
        cin >> t[i];
        p2.pb(mod(p2.back() * 2));
    }
    t.insert(t.begin(), 0);
    partial_sum(all(t), t.begin());
    ll ans = 0;
    ll cur = p2[n], curleft = 1;
    rep(i, 1, n+1){
        ll left = min(ll(i), T - t[i]);
        if(left < 0) break;
        if(left == i) {
            cur = p2[n];
        }
        else{
            cur = mod(cur - inv2 * mod(C(i-1, curleft) * p2[n - (i - 1)]));
        }
        while(curleft > left){
            cur = mod(cur - mod(C(i, curleft) * p2[n - i]));
            curleft--;
        }
        curleft = left;
        ans = mod(ans + cur);
    }
    if(ans < 0) ans += MOD;
    rep(i, 0, n){
        ans = mod(ans * inv2);
    }
    cout << ans << "\n";
    
    return 0;
}
