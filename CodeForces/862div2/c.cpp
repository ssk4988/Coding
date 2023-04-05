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
        int n, m; cin >> n >> m;
        vl ks(n);
        rep(i, 0, n){
            cin >> ks[i];
        }
        sort(all(ks));
        rep(i, 0,m){
            ll a,b,c;cin>>  a >> b >> c;
            ll ac4 = 4 * a * c;
            bool hasans = false;
            ll ans = -1;
            if(ac4 > 0){
                ll sq = sqrtl(ac4);
                ll pos = sq * sq == ac4 ? sq - 1 : sq;
                auto it = lower_bound(all(ks), b - pos);
                if(it != ks.end() && (*it) <= b + pos){
                    hasans = true;
                    ans = *it;
                }
                it = upper_bound(all(ks), b + pos);
                if(it != ks.begin()){
                    it = prev(it);
                    if(*it >= b - pos){

                        hasans = true;
                        ans = *it;
                    }
                }
            }
            if(hasans){
                cout << "YES\n";
                cout << ans << nL;
            }
            else{
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}
