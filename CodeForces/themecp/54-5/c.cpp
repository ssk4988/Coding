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

const ll mod = 1e9+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll ans = 0;
    const int LIM = 2e5+10;
    vvi divs(LIM);
    rep(i, 1, LIM){
        for(int j = i; j < LIM; j += i) {
            divs[j].pb(i);
        }
    }
    rep(ab, 2, n) {
        int c = n - ab;
        assert(c > 0);
        vi cnt(sz(divs[ab]));
        for(int i = sz(divs[ab])-1; i >= 0; i--){
            cnt[i] = ab / divs[ab][i] - 1;
            rep(j, i+1, sz(cnt)){
                if(divs[ab][j] % divs[ab][i] == 0) cnt[i] -= cnt[j];
            }
        }
        rep(i, 0, sz(divs[ab])){
            ll cont = c * divs[ab][i] / __gcd(c, divs[ab][i]);
            cont %= mod;
            (ans += cont * cnt[i]) %= mod;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
