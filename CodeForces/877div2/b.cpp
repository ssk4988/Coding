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
        vi p(n), rev(n);
        rep(i, 0, n){
            cin >> p[i];
            p[i]--;
            rev[p[i]] = i;
        }
        vi vals;
        vals.pb(rev[0]);
        vals.pb(rev[n - 1]);
        vals.pb(rev[1]);
        sort(all(vals));
        if(vals[0] == rev[n - 1]){
            cout << (vals[0] + 1) << " " << (vals[1] + 1) << nL;
        }
        else if(vals[1] == rev[n - 1]){
            cout << (vals[0] + 1) << " " << (vals[0] + 1) << nL;
        }
        else{
            cout << (vals[2] + 1) << " " << (vals[1] + 1) << nL;
        }
    }
    
    return 0;
}
