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
using vvl = vector<vl>;

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

ll MOD = 998244353;
ll mod(ll k)
{
    return k % MOD;
}

const int LIM = 10000;
const int maxn = 5100;
const int BLANK = 0;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i, 2, LIM)
    {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int n, int k)->ll{
        if(n < 0 || k < 0 || k > n) return 0;
        return mod(fact[n] * mod(invfact[k] * invfact[n - k]));
    };
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n; cin >> n;
        int n2 = n / 2;
        vi freq(n);
        rep(i, 0, n)
        {
            int k;
            cin >> k;
            k--;
            freq[k]++;
        }
        vi order;
        for(int i = n - 1; i >= 0; i--) if(freq[i]) order.pb(i);
        vvl dp(n + 1, vl(n + 1, BLANK)); // idx used, num bigs used
        dp[0][0] = 1;
        int pref = 0;
        rep(i, 0, sz(order)){
            int v = order[i];
            int pref1 = pref + freq[v];
            rep(bigs, 0, pref + 1){
                if(dp[pref][bigs] == BLANK) continue;
                int smalls = pref - bigs;
                int holes = max(0, bigs - 1 + (bigs == n2));
                int left = holes - smalls;
                // put all in holes
                dp[pref1][bigs] = mod(dp[pref1][bigs] + mod(dp[pref][bigs] * choose(left, freq[v])));
                // put 1 in bigs
                if(bigs < n2){
                    dp[pref1][bigs + 1] = mod(dp[pref1][bigs + 1] + mod(dp[pref][bigs] * choose(left, freq[v] - 1)));
                }
            }
            pref += freq[v];
        }
        cout << dp[n][n2] << nL;
    }

    return 0;
}
