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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl m(n), p(n);
        vvi bucket(n+1);
        int own = 0;
        int pd = 0;
        set<pi> buy;
        vpi order;
        rep(i, 0, n){
            cin >> m[i] >> p[i];
            bucket[m[i]].pb(i);
            buy.insert({p[i], i});
            order.pb({m[i], i});
        }
        sort(all(order));
        vi idx(n);
        rep(i, 0, n){
            idx[order[i].s] = i;
        }
        ll ans = 0;
        set<pi> bought;
        set<pi> unbuy;
        while(own < n){
            while(pd <= own){
                for(int i : bucket[pd]){
                    if(buy.count({p[i], i})){
                        buy.erase({p[i], i});
                        own++;
                    }
                }
                pd++;
            }
            if(own >= n) continue; 
            while(sz(bought) && m[bought.begin()->s] <= own){
                auto [i, x] = *bought.begin();
                bought.erase({i, x});
                unbuy.insert({p[x], x});
            }
            if(sz(unbuy)){
                auto [c1, i1] = *prev(unbuy.end());
                ans -= c1;
                unbuy.erase(prev(unbuy.end()));
            }
            auto [c2, i2] = *buy.begin();
            ans += c2;
            buy.erase(buy.begin());
            bought.insert({idx[i2], i2});
            own++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
