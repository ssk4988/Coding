#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;
using vl = vector<ll>;
ll MOD = 1e9 + 7;
ll mod(ll k) {
    return k % MOD;
}
ll modpow(ll b, ll p){
    if(p== 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p/2);
    res = mod(res * res);
    res = mod(res * modpow(res, p%2));
    return res;
}

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    ll a1, a2, b1, b2, k; 
    cin >> a1 >> a2 >> b1 >> b2 >> k;
    vl flocks;
    auto dfs = [&](ll cur, auto &&dfs)->void{
        if(cur > ll(1e9)) return;
        if(cur) flocks.pb(cur);
        // cout << cur << "\n";
        dfs(cur * 10 + 3, dfs);
        dfs(cur * 10 + 8, dfs);
    };
    dfs(0, dfs);
    flocks.pb(-1);
    flocks.pb(ll(1e9) + 1);
    // cout << sz(flocks) << "\n";
    sort(all(flocks));

    ll ans = 0;
    rep(i, 1, sz(flocks) - 1){
        if(i + k >= sz(flocks)) break;
        ll leftstart = flocks[i - 1] + 1;
        ll leftend = flocks[i];
        ll rightstart = flocks[i + k - 1];
        ll rightend = flocks[i + k] - 1;

        ll astart = max(a1, leftstart), aend = min(a2, leftend);
        ll bstart = max(b1, rightstart), bend = min(b2, rightend);
        if(astart <= aend && bstart <= bend){
            ans = mod(ans + mod((aend - astart + 1) * (bend - bstart + 1)));
        }
         astart = max(a1, rightstart), aend = min(a2, rightend);
        bstart = max(b1, leftstart), bend = min(b2, leftend);
        if(astart <= aend && bstart <= bend){
            ans = mod(ans + mod((aend - astart + 1) * (bend - bstart + 1)));
        }
    }
    ll denom = mod((a2 - a1 + 1) * (b2 - b1 + 1));
    denom = modpow(denom, MOD - 2);
    ans = mod(ans * denom);
    cout << ans << "\n";
}
