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
    int n; ld a, b;
    cin >> n >> a >> b;
    vpi v(n);
    rep(i, 0, n){
        cin >> v[i].f >> v[i].s;
    }
    if(n == 1){
        cout << fixed << setprecision(8) << max(a / v[0].f, b / v[0].s) << "\n";
        return 0;
    }
    int besta = 0;
    rep(i, 0, n){
        if(v[i].f < v[besta].f) besta = i;
    }
    int besta2 = besta == 0 ? 1 : 0;
    rep(i, 0, n){
        if(i == besta) continue;
        if(v[i].f < v[besta2].f) besta2 = i;
    }
    int bestb = 0;
    rep(i, 0, n){
        if(v[i].s < v[bestb].s) bestb = i;
    }
    int bestb2 = bestb == 0 ? 1 : 0;
    rep(i, 0, n){
        if(i == bestb) continue;
        if(v[i].s < v[bestb2].s) bestb2 = i;
    }
    ld ans = 0;
    for(int i : {besta, besta2}){
        for(int j : {bestb, bestb2}){
            if(i == j) continue;
            ans = max(ans, a / v[i].f + b / v[j].s);
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}