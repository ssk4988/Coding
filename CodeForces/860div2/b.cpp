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
        int m; cin >> m;
        vvi a(m);
        vi lastocc(50005);
        vvi winns(m);
        rep(i, 0, m){
            int n1; cin >> n1;
            a[i].resize(n1);
            rep(j, 0, n1){
                cin >> a[i][j];
                lastocc[a[i][j]] = i;
            }
        }
        vi ans;
        rep(i, 0, m){
            rep(j, 0, sz(a[i])){
                if(lastocc[a[i][j]] == i){
                    winns[i].pb(a[i][j]);
                }
            }
            if(sz(winns[i]) <= 0){
                ans.clear();
                ans.pb(-1);
                break;
            }
            else{
                ans.pb(winns[i][0]);
            }
        }
        rep(i, 0, sz(ans)){
            cout << ans[i] << " " ;
        }
        cout << nL;
    }
    
    return 0;
}
