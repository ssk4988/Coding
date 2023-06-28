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
using vvl = vector<vl>;

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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        vl a(n);
        vvi idx(n + 1);
        vl occ(n + 1);
        rep(i, 0, n){
            cin >> a[i];
            idx[a[i]].pb(i);
        }
        set<pi> ints;
        ints.insert({0, n - 1});
        occ[n] += n;
        for(int i = n; i > 0; i--){
            for(int j : idx[i]){
                auto it = ints.upper_bound({j, n + 5});
                it = prev(it);
                auto [l, r] = *it;
                if(r < j || j < l) assert(false); // can this even happen???
                int r1 = j - 1, l1 = j + 1;
                ints.erase(it);
                occ[r - l + 1] -= i;
                if(l <= r1){
                    ints.insert({l, r1});
                    occ[r1 - l + 1] += i;
                }
                if(l1 <= r){
                    ints.insert({l1, r});
                    occ[r - l1 + 1] += i;
                }
            }
        }
        // check if all are n what happens
        ll m; cin >> m;
        ll ans = 0;
        for(int i = n; i > 0; i--){
            ll numtomake = min(occ[i], (m + i - 1) / i);
            ll extract = min(numtomake * i, m);
            m -= extract;
            ans += extract - numtomake;
        }
        cout << ans << nL;
    }
    
    return 0;
}
