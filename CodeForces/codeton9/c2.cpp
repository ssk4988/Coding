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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll x, m; cin >> x >> m;
        int bit = __lg(x);
        ll md = 1LL << (bit+1);
        vll places;
        for(ll z = 0; true; z += x){
        // for(ll y = 1; true; y++){
            ll y = x ^ z;
            // if(y == 0) continue;
            places.push_back({z, z % md});
            if(sz(places) > 1 && places[0].s == places.back().s){
                break;
            }
            // if(z % x == 0) {
            // }
        }
        ll ans = 0;
        ll cycle = places.back().f - places[0].f;
        rep(i, 0, sz(places)-1){
            auto [z, zm] = places[i];
            ll y = z ^ x;
            ll under = 1 + (m - y) / cycle;
            if(m < y) under = 0;
            ans += under;
            if(y == 0) ans--;
        }

        // ll cycles = (m - places[0].f) / cycle;
        // rep(i, 0, sz(places) - 1){
        //     ll v = places[i].f + cycles * cycle;
        //     if(v <= m) ans++;
        // }

        // for(ll y = 1; y <= m; y++){
        //     ll z = x ^ y;
        //     if(z % x == 0) cout << y << " " << z << " " << y % 8 << "\n";
        // }
        for(ll y = 1; y <= min(5 * x, m); y++) {
            ll z = x ^ y;
            if(z % y == 0 && z % x != 0) ans++;
            // if(z % x == 0) ans--;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
