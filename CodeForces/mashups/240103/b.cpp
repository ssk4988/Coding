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
    int n; ll d; cin >> n >> d;
    vector<vl> tstart(n), tend(n), dstart(n), dend(n), v(n);
    rep(i, 0, n){
        int k; cin >> k;
        tstart[i].resize(k), tend[i].resize(k), dstart[i].resize(k), dend[i].resize(k), v[i].resize(k);
        ll trav = 0, curt = 0;
        rep(j, 0, k){
            cin >> v[i][j]; int t; cin >> t;
            dstart[i][j] = trav, tstart[i][j] = curt;
            curt += t;
            trav += v[i][j] * t;
            dend[i][j] = trav, tend[i][j] = curt;
        }
    }
    auto eval = [](ll v, ll d, ll t) -> ll { return d + v * t; };
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, i){
            int k1 = sz(v[i]), k2 = sz(v[j]);
            int p1 = 0, p2 = 0;
            int prewin = 0;
            while(p1 < k1 && p2 < k2){
                ll ts = max(tstart[i][p1], tstart[j][p2]), te = min(tend[i][p1], tend[j][p2]);
                ll cond1 = eval(v[i][p1], dstart[i][p1], ts - tstart[i][p1]) - eval(v[j][p2], dstart[j][p2], ts - tstart[j][p2]);
                ll cond2 = eval(v[i][p1], dstart[i][p1], te - tstart[i][p1]) - eval(v[j][p2], dstart[j][p2], te - tstart[j][p2]);
                if(cond1 != 0) cond1 /= abs(cond1);
                if(cond2 != 0) cond2 /= abs(cond2);
                if(cond2 != 0){
                    if(prewin != 0 && cond2 != prewin) ans++;
                    prewin = cond2;
                }
                // if(cond1 == 0 && cond2 != 0 && ts != 0) ans++;
                // else if(cond1 != 0 && cond1 == -1 * cond2) ans++;
                if(tend[i][p1] < tend[j][p2]) p1++;
                else if(tend[i][p1] == tend[j][p2]) p1++, p2++;
                else p2++;
            }
        }
    }
    cout << ans << nL;
    
    return 0;
}
