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
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        sort(all(a));
        a = {a[0], a[1], a[n-2], a[n-1]};
        int ans = abs(a[0] - a[2]) + abs(a[2] - a[1]) + abs(a[1] - a[3]) + abs(a[3] - a[0]);
        // for(auto x : a){
        //     for(auto y : a){
        //         ans += abs(x - y);
        //     }
        // } 
        // ans /=2;
        cout << ans << nL;
    }
    
    return 0;
}
