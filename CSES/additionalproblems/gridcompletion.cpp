#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
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

const ll MOD = 1e9 + 7;

struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  while (sz(t) <= n) {
    int64_t i = sz(t),
            inv = MOD - (MOD / i) * t[MOD % i].inv % MOD;
    t.push_back({inv, i * t[i - 1].fact % MOD,
      inv * t[i - 1].inv_fact % MOD});
  }
}
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % MOD *
    t[n - k].inv_fact % MOD;
}

const int N = 501;
int dp[N][N][N];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, -1, sizeof dp);
    int n; cin >> n;
    vector<string> grid(n);
    rep(i, 0, n){
        cin >> grid[i];
    }
    vi ac(n, -1), bc(n, -1);
    rep(c, 0, n){
        rep(r, 0, n){
            if(grid[r][c] == 'A') ac[c] = r;
            if(grid[r][c] == 'B') bc[c] = r;
        }
    }
    // 0 - off board, 1 - on board, 2 - matched
    ll cleared = 0;
    vi astate(n), bstate(n);
    rep(i, 0, n){
        if(ac[i] != -1 && bc[i] != -1){
            astate[ac[i]] = bstate[bc[i]] = 2;
        } else if(ac[i] != -1) astate[ac[i]] = 1;
        else if(bc[i] != -1) bstate[bc[i]] = 1;
        else cleared++;
    }

    vi cnt(9);
    rep(i, 0, n) {
        cnt[bstate[i] * 3 + astate[i]]++;
    }

    auto go = [&](int ona, int onb, int offb, auto &&go) -> ll {
        int &ans = dp[ona][onb][offb];
        if(ans != -1) return ans;
        if(ona == 0 && onb == 0 && offb == 0) return ans = 1;
        assert(onb >= 0 && ona >= 0 && offb >= 0);
        ll res = 0;
        if(ona) {
            if(offb) (res += offb * go(ona-1, onb, offb-1, go)) %= MOD;
        } else {
            if(offb) (res += offb * go(ona, onb, offb-1, go)) %= MOD;
            if(onb) (res += onb * go(ona, onb-1, offb, go)) %= MOD;
        }
        return ans = res;
    };

    int ona = 0, onb = 0;
    int matcheda = 0, matchedb = 0;
    int offa = 0, offb = 0;
    rep(a, 0, 3) {
        rep(b, 0, 3) {
            if(a == 2) matcheda += cnt[b*3+a];
            if(a == 1) ona += cnt[b*3+a];
            if(a == 0) offa += cnt[b*3+a];
            if(b == 2) matchedb += cnt[b*3+a];
            if(b == 1) onb += cnt[b*3+a];
            if(b == 0) offb += cnt[b*3+a];
        }
    }

    ll ans = 0;
    rep(i, 0, 1 + cnt[0]) {
        rep(j, 0, 1 + cnt[3]) {
            rep(k, 0, 1 + cnt[1]) {
                offa -= i;
                offb -= i;
                offa -= j;
                onb -= j;
                ona -= k;
                offb -= k;
                ll ways = (C(cnt[0], i) * C(cnt[3], j)) % MOD * C(cnt[1], k) % MOD;
                int par = (i + j + k) % 2 == 0 ? 1 : -1;
                ll w = go(ona, onb, offb, go);
                (ans += w * ways * par) %= MOD;
                offa += i;
                offb += i;
                offa += j;
                onb += j;
                ona += k;
                offb += k;
            }
        }
    }
    grow(2 * n + 10);
    (ans += MOD) %= MOD;
    (ans *= t[cleared].fact) %= MOD;
    cout << ans << "\n";

    return 0;
}
