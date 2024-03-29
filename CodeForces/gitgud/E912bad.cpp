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



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    vl p;
    cin >> n;
    p = vl(n);
    rep(i, 0, n){
        cin >> p[i];
    }
    ll k; cin >> k;
    auto test = [&](ll LIM) -> bool {
        ll ans = 0;
        rep(mask, 0, 1 << n){
            ll prod = 1;
            int sign = 1;
            rep(i, 0, n){
                if((mask >> i) & 1){
                    sign *= -1;
                    prod *= p[i];
                }
            }
            ans += LIM / prod * sign;
        }
        ans = LIM - ans;
        // cout << LIM << " " << ans << "\n";
        return ans >= k;
    };
    ll x = 0;
    for(ll dif = 1LL << 60; dif; dif >>= 1){
        if(!test(x + dif)) x += dif;
    }
    cout << ++x << "\n";
    
    return 0;
}
