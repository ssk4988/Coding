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

ll nc3(ll x){
    return x * (x-1) * (x-2) / 6;
}
ll nc2(ll x) {
    return x * (x-1) / 2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    const int LIM = 4e5+20;
    vvi divs(LIM);
    rep(i, 1, LIM){
        for(int j = i; j < LIM; j += i){
            divs[j].pb(i);
        }
    }
    
    rep(cn, 0, nc){
        ll l, r; cin >> l >> r; r++;
        ll ans = nc3(r-l);
        rep(k, l, r){
            int cnt = 0;
            for(int d : divs[k]){
                if(d >= l && d < r && d < k) cnt++;
            }
            ans -= nc2(cnt);
            int p = 1;
            while(k % (p * 2) == 0) p *= 2;
            p *= 2;
            for(int i : divs[2 * k]) {
                if (i < l || i >= k) continue;
                for(int j : divs[2 * k]) {
                    if (j < l || j >= i) continue;
                    if((i % p == 0 || j % p == 0) && i + j > k) ans--;
                }
            }
        }

        cout << ans << "\n";
    }    
    
    return 0;
}
