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
using ull = unsigned ll;
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

mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int LIM = 2e6 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
ll MOD = 998244353;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int a, int b) -> ll{
        return mod(fact[a] * mod(invfact[a - b] * invfact[b]));
    };
    auto catalan = [&](int a)->ll{
        // if(a == 0) return 1;
        return mod(fact[2*a] * mod(mod(invfact[a] * invfact[a]) * inv[a + 1]));
    };
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vpi v(k);
        vector<ull> hashes(n + 1);
        rep(i, 0, k){
            cin >> v[i].f >> v[i].s;
            v[i].f--;
            auto x = rng();
            hashes[v[i].f] ^= x;
            hashes[v[i].s] ^= x;
        }
        // int x = rand();
        // hashes[0] ^= x;
        // hashes[n] ^= x;
        rep(i, 0, sz(hashes)) hashes[i + 1] ^= hashes[i];
        hashes.pop_back();
        sort(all(hashes));
        ll ans = 1;
        for(int l = 0; l < n; l++){
            int r = l;
            while(r + 1 < n && hashes[r + 1] == hashes[r]) r++;
            int len = r - l + 1;
            if(len % 2 == 1){
                ans = 0;
                break;
            }
            else ans = mod(ans * catalan(len / 2));
            l = r;
        }
        cout << ans << nL;
    }
    
    return 0;
}
