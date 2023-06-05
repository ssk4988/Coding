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
        vector<unordered_map<int, ll>> ps(n + 1);
        vl a(n), b(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n) cin >> b[i];
        rep(i, 0, n){
            ps[a[i]][b[i]]++;
        }
        ll ans = 0;
        rep(i, 0, n){
            int bj = a[i] * a[i] - b[i];
            if(ps[a[i]].count(bj)){
                ans += ps[a[i]][bj];
            }
        }
        rep(i, 1, 2 * n + 1){
            if(i * i > 2 * n) break;
            if((i * i) % 2 == 0 && ps[i].count(i * i / 2)){
                ans -= ps[i][i * i / 2];
            }
        }
        ans /= 2;
        rep(i, 0, n){
            int other = 2 * n / a[i];
            int upb = min(int(a[i] - 1), other);
            rep(aj, 0, upb + 1){
                if(ps[aj].count(a[i] * aj - b[i])) ans += ps[aj][a[i] * aj - b[i]];
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
