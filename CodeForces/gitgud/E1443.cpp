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

ll nc2(ll v){
    return v * (v-1) / 2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    ll x = 0;
    int m = min(16, n);
    int al = 0, ar = n - m;
    vl fact(m + 5);
    fact[0] = 1;
    rep(i, 1, sz(fact)) fact[i] = fact[i-1] * i;
    rep(_, 0, q){
        int t; cin >> t;
        if(t == 1){
            int l, r; cin >> l >> r; l--;
            ll ans = r - l;
            if(l < ar){
                ans += nc2(min(ar, r)) - nc2(l);
            }
            if(r <= ar){
                cout << ans << "\n";
                continue;
            }
            r -= ar;
            l = max(ar, l) - ar;
            ll x1 = x;
            vi a, pos(m);
            iota(all(pos), 0);
            rep(i, 0, m){
                ll idx = x1 / fact[m - 1 - i];
                a.pb(pos[idx]);
                pos.erase(pos.begin() + idx);
                x1 -= fact[m - 1 - i] * idx;
            }
            rep(i, l, r){
                ans += a[i] + ar;
            }
            cout << ans << "\n";
        }
        else{
            ll nex; cin >> nex; x += nex;
        }
    }
    
    return 0;
}
