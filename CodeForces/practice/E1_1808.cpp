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

int n, k;
ll MOD;
int LIM = 500;
vl inv(LIM);
vl fact(LIM), invfact(LIM);
int BLANK = -1;
int target;
// vector<vvl> dp;
ll dp[105][32];

int good[50];
// vi good;

ll mod(ll k){
    if(k >= MOD){
        return k % MOD;
    }
    return k;
}

ll solve(int left, int curmod){
        if(dp[left][curmod] != BLANK) return dp[left][curmod];
        if(left == 0){
            // if(usedtarget) cout << "Yahoo!" << nL;
            dp[left][curmod] = (target == curmod ? 1 : 0);
            return dp[left][curmod];
        }
        dp[left][curmod] = 0;
        int lim = good ? 0 : left;
        rep(i, 0, k){
            if(good[i])continue;
            // if(i == 0 && curdig == target) continue;
            int newmod = (i + curmod) % k;
            dp[left][curmod] = (dp[left][curmod] + solve(left - 1, newmod))% MOD;
            // if(left == n){
            //     cout << "ans is " << dp[left][curmod] << " after taking " << i << " " << curdig << "'s" << nL;
            // }
        }
        // cout << "used: " << left << " target: " << target << " curmod: " << curmod << " usedtarget: " << usedtarget << " curdig: " << curdig << " ans: " << dp[left][curmod] << nL;
        return dp[left][curmod];
    }

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k >> MOD;
    inv[1] = fact[1] = invfact[1] = 1;
    inv[0] = fact[0] = invfact[0] = 1;
    rep(i, 2, LIM)
    {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = (i * fact[i - 1]) % MOD;
        invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
        // assert((invfact[i] * fact[i]) % MOD == 1);
    }
    
    
    ll ans = 0;
    map<int, int> freq;
    rep(i, 0, k){
        freq[(i * 2) % k]++;
    }
    ll total = 1;
    rep(i, 0, n){
        total = (total * k) % MOD;
    }
    rep(i, 0, k){
        // if(freq[i] == 0) continue;
        // good = vi(k);
        memset(good, 0, sizeof good);
        rep(j, 0, k){
            if((j * 2) % k == i) good[j] = true;
        }
        target = i;
        memset(dp, BLANK, sizeof dp);
        // dp = vector<vvl>(n + 1, vvl(k, vl(k + 1, BLANK)));
        ans = (ans + solve(n, 0));
    }
    cout << ((total - ans) % MOD + MOD) % MOD << nL;
    // for(auto &p : freq){
    //     cout << p.f << " freq " << p.s << nL;
    // }
    return 0;
}
