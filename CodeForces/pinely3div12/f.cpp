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

const ll MOD = 998244353;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        // ADD MOD
        int n; cin >> n;
        vl a(n + 1);
        ll def = 0, emp = 0;
        ll ans = 1;
        bool works = true;
        rep(i, 1, n + 1){
            cin >> a[i];
            if(a[i] > i) works = false;
            if(!works) continue;
            else if(a[i] == a[i - 1]){
                // ans = ans
                def++, emp++;
            }
            else if(a[i] == a[i - 1] + 1){
                ans = mod(ans * mod(emp + 1 + def));
            }
            else if(a[i] == a[i - 1] + 2){
                ans = mod(ans * mod(emp * def));
                emp--, def--;
            }
            else{
                works = false;
            }
            if(emp < 0 || def < 0) works = false;
        }
        if(emp != 0 || def != 0 || a.back() != n) works = false;
        if(!works) cout << 0 << nL;
        else cout << ans << nL;
    }
    
    return 0;
}
