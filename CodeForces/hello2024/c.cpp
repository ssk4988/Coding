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
        int inf = 1e9;
        array<int, 3> sc = {0, inf, inf};
        rep(i, 0, n){
            cin >> a[i];
            if(a[i] <= sc[2]){
                sc[2] = a[i];
            }
            else if(a[i] <= sc[1]){
                sc[1] = a[i];
            }
            else{
                sc[2] = a[i];
                sc[0]++;
            }
            if(sc[1] < sc[2]) swap(sc[1], sc[2]);
        }
        cout << sc[0] << nL;
    }
    
    return 0;
}
