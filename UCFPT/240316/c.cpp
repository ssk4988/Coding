#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> m >> n;
    vl a(m);
    rep(i, 0, n){
        int k; cin >> k;
        rep(j, 0, k){
            int l; cin >> l;
            a[l] |= 1LL << i;
        }
    }
    unordered_map<ll, ll> dp;
    // vector<ll> dp(1 << n, -1);
    dp[0] = 0;
    rep(i, 0, n){
        dp[1LL << i] = 0;
    }
    auto go = [&](ll mask, auto &&go) -> ll {
        // cout << mask << endl;
        if(dp.count(mask)) {
            return dp[mask];
        }
        // ll &ans = dp[mask];
        // if(ans != -1) return ans;
        ll ans = 1e9;
        rep(i, 0, m){
            ll with = mask & a[i]; ll notwith = mask & (~a[i]);
            if(with == mask || notwith == mask) continue;
            ll cur = go(with, go) + go(notwith, go) + __builtin_popcountll(mask);
            ans = min(ans, cur);
            // if(__builtin_popcount(with)){ 
            //     cur += go(with, go) / __builtin_popcount(with);
            //     int wd = 0;
            //     rep(j, 0, n){
            //         if((with >> j) & 1){
            //             wd += go()
            //         }
            //     }
            // }
        }
        dp[mask] = ans;
        return ans;
    };
    ll res = go((1LL << n) - 1, go);
    if(res >= 1e6){
        cout << "not possible\n";
    }
    else{
        cout << fixed << setprecision(8) << ((long double)(res) / n) << "\n";
    }
    return 0;
}