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
        vpi a(n);
        rep(i, 0, n){
            cin >> a[i].f;
        }
        rep(i, 0, n) cin >> a[i].s;
        sort(all(a));
        // sort(all(a), [](pi a, pi b) -> bool {
        //     return a.f < b.f && a.s < b.s;
        // });
        rep(i, 0, n) cout << a[i].f << " ";
        cout << nL;
        rep(i, 0, n){
            cout << a[i].s << " ";
        }
        cout << nL;
    }
    
    return 0;
}