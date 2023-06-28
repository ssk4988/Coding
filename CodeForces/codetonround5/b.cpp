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
        int n; ll target; cin >> n >> target;
        vl a(n), b(n), c(n);
        ll val = 0;
        rep(i, 0, n) cin >> a[i];
        rep(i, 0, n) cin >> b[i];
        rep(i, 0, n) cin >> c[i];
        rep(i, 0, n){
            if(((val | a[i]) & ~target) > 0) break;
            else val |= a[i];
        }
        rep(i, 0, n){
            if(((val | b[i]) & ~target) > 0) break;
            else val |= b[i];
        }
        rep(i, 0, n){
            if(((val | c[i]) & ~target) > 0) break;
            else val |= c[i];
        }
        if(val == target) cout << "Yes\n";
        else cout << "No\n";
    }
    
    return 0;
}
