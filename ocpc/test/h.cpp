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
const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; (b*=b)%=mod, e/=2)
        if(e&1) (res*=b)%=mod;
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n; cin >> n;
    n -= 2;
    vi precomp{1, 1, 2, 3, 4, 6, 9, 12, 18, 27};
    if(n < sz(precomp)) {
        cout << precomp[n] << "\n";
        return 0;
    }
    ll p3 = n/3;
    ll p43 = (n % 3) >= 1;
    ll p32 = (n % 3) >= 2;
    ll ans = modpow(3, p3) * modpow(4, p43) % mod * modpow(modpow(3, mod-2), p43) % mod * modpow(3, p32) % mod * modpow(modpow(2, mod-2), p32) % mod;
    cout << ans << "\n";
    
    return 0;
}
