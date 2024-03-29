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
    vl l(2), r(2);
    cin >> l[0] >> r[0] >> l[1] >> r[1];
    l[0]--, l[1]--;
    int times = 0;
    ll pw = 2;
    ll ans = 0;
    while(times < 32){
        vector<vl> occ(2);
        vector<vl> start(2);
        vector<vl> finish(2);
        rep(i, 0, 2){
            for(ll mid = l[i] / pw * pw + (pw >> 1) - 1; mid < r[i]; mid += pw){
                occ[i].pb(mid);
                start[i].pb(max(l[i], mid / pw * pw) - mid / pw * pw);
                finish[i].pb(min(r[i], mid / pw * pw + pw - 1) - mid / pw * pw);
                if(sz(occ[i]) >= 2) break;
            }
        }
        rep(i, 0, sz(occ[0])){
            rep(j, 0, sz(occ[1])){
                ans = max(ans, min(finish[0][i], finish[1][j]) - max(start[0][i], start[1][j]));
            }
        }
        pw *= 2;
        times++;
    }
    cout << ans << "\n";
    
    return 0;
}
