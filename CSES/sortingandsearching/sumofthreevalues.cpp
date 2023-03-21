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
    int n;
    ll x; cin >> n >> x;
    vpl a(n);
    rep(i, 0, n){
        cin >> a[i].f;
        a[i].s = i + 1;
    }
    vl ans = {-1};
    sort(all(a));
    rep(i, 0, n){
        int r = n - 1;
        rep(l, i + 1, n){
            if(l >= r) break;
            while(a[l].f + a[r].f > x - a[i].f) r--;
            if(l >= r) break;
            if(a[l].f + a[r].f == x - a[i].f){
                ans = {a[i].s, a[l].s, a[r].s};
            }
        }
    }
    if(ans[0] == -1){
        cout << "IMPOSSIBLE\n";
    }
    else{
        rep(i, 0, 3){
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
