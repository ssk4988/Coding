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

const ll MOD = 998244353;
const ll inv2 = 499122177;
inline ll mod(ll k){
    return k % MOD;
}

ll modpow(ll b, ll p){
    ll res = 1;
    for(; p; p >>= 1, b = mod(b * b)){
        if(p & 1) res = mod(res * b);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    const int MAX_A = 1e5 + 10;
    vl a(n), freq(n), sum2(MAX_A), sumtot(MAX_A), cnt(MAX_A), p2(MAX_A, 1);
    vi mobius(MAX_A);
    mobius[1] = 1;
    rep(i, 1, sz(mobius)){
        for(int j = 2 * i; j < sz(mobius); j += i){
            mobius[j] -= mobius[i];
        }
    }
    // rep(i, 1, 10){
    //     cout << i << " " << mobius[i] << endl;
    // }
    vvi divs(MAX_A);
    rep(i, 1, MAX_A){
        for(int j = i; j < MAX_A; j += i){
            divs[j].pb(i);
        }
    }
    rep(i, 0, n){
        cin >> a[i] >> freq[i];
        for(int j : divs[a[i]]){
            sum2[j] = mod(sum2[j] + freq[i] * mod(a[i] * a[i]));
            sumtot[j] = mod(sumtot[j] + freq[i] * a[i]);
            cnt[j] = cnt[j] + freq[i];
            p2[j] = mod(p2[j] * modpow(2, freq[i]));
        }
    }
    auto solve = [&](int g) -> ll {
        sumtot[g] = mod(sumtot[g] * sumtot[g]);
        sumtot[g] = mod(mod(sumtot[g] - sum2[g]) + MOD);
        ll ans = 0;
        if(cnt[g] >= 2) {
            ans = mod(sum2[g] * mod(mod(cnt[g] - 1) * mod(p2[g] * modpow(inv2, 2))));
            ans = mod(ans + mod(sumtot[g] * mod(p2[g] * modpow(inv2, 2))));
        }
        if(cnt[g] >= 3){
            ans = mod(ans + mod(sumtot[g] *  mod(mod(cnt[g] - 2) * mod(p2[g] * modpow(inv2, 3)))));
        }
        return ans;
    };
    ll ans = 0;
    rep(i, 1, MAX_A){
        ll res = solve(i);
        ans = mod(ans + mod(mod(mobius[i] * res) + MOD));
    }
    cout << ans << "\n";
    
    return 0;
}
