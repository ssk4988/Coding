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
    ll xlim = 2e9;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<vl> d(2, vl(n));
        rep(i, 0, 2){
            rep(j, 0, n) cin >> d[i][j];
        }
        bool found = false;
        rep(mat2, 0, n){
            if(found) break;
            rep(side, 0, 2){
                if(found) break;
                ll p1 = d[0][0], p2 = (side ? -1 : 1) * d[1][mat2];
                vl p = {p1, p2};
                vector<multiset<ll>> rem(2);
                vl h;
                rep(i, 0, n){
                    if(i > 0) rem[0].insert(d[0][i]);
                    if(i != mat2) rem[1].insert(d[1][i]);
                }
                h.pb(0);
                bool valid = true;
                rep(i, 0, n - 1){
                    ll x, me, you;
                    if(*rem[0].rbegin() >= *rem[1].rbegin()){
                        x = *rem[0].rbegin();
                        me = 0, you = 1;
                    }
                    else{
                        x = *rem[1].rbegin();
                        me = 1, you = 0;
                    }
                    ll h1;
                    if(p[me] >= p[you]){
                        h1 = p[me] - x;
                    }
                    else{
                        h1 = p[me] + x;
                    }
                    if(rem[you].find(abs(h1 - p[you])) != rem[you].end()){
                        h.pb(h1);
                        rem[me].erase(rem[me].find(x));
                        rem[you].erase(rem[you].find(abs(h1 - p[you])));
                    }
                    else{
                        valid = false;
                        break;
                    }
                }
                if(valid){
                    found = true;
                    ll mind = LLONG_MAX, maxd = LLONG_MIN;
                    for(ll x : p){
                        mind = min(mind, x), maxd = max(maxd, x);
                    }
                    for(ll x : h){
                        mind = min(mind, x), maxd = max(maxd, x);
                    }
                    ll adj = 0;
                    if(mind < 0) adj = abs(mind);
                    else if(maxd > xlim) adj = xlim - maxd;
                    for(ll &x : p) x += adj;
                    for(ll &x : h) x += adj;
                    cout << "YES\n";
                    for(ll &x : h) cout << x << " ";
                    cout << nL;
                    for(ll &x : p) cout << x << " ";
                    cout << nL;
                }
            }
        }
        if(!found) cout << "NO\n";
    }
    
    return 0;
}
