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

ll MOD = 998244353;
ll mod(ll k){
    return k % MOD;
}
ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p/2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

ll modinv(ll k){
    return modpow(k, MOD - 2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    auto calc = [](int common, int d1, int d2)->ll{
        if(d1 == 0 && d2 == 0){
            return common + 1;
        }
        else if(d1 == 0 && d2 == 1){
            return common + 1 + (common % 2);
        }
        else if(d1 == 1 && d2 == 0){
            return common + 1 + (common % 2 == 0);
        }
        assert(false);
    };
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        ll sum = 0;
        auto solve = [&](vl &cur, int bitnum, int bitsused, auto &&solve)->void{
            if(sz(cur) == 0) return;
            if(bitnum == -1){
                sum += calc(bitsused, 0, 0) * sz(cur) * sz(cur);
                return;
            }
            vl cur0, cur1;
            for(ll i : cur){
                if(i & (1 << bitnum)){
                    cur1.pb(i);
                }
                else cur0.pb(i);
            }
            sum += calc(bitsused, 0, 1) * sz(cur0) * sz(cur1);
            sum += calc(bitsused, 1, 0) * sz(cur1) * sz(cur0);
            solve(cur0, bitnum-1, bitsused, solve);
            solve(cur1, bitnum-1, bitsused + 1, solve);
        };
        solve(a, 29, 0, solve);
        ll ans = mod(mod(sum) * modinv(mod(ll(n) * n)));
        cout << ans << nL;
    }
    
    return 0;
}