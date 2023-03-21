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
    int n, x; cin >> n >> x;
    vpi a(n);
    rep(i, 0, n){
        cin >> a[i].f;
        a[i].s = i;
    }
    sort(all(a));
    int r = n - 1;
    pi ans = {-1, -1};
    rep(l, 0, n){
        if(l >= r) break;
        while(a[l].f + a[r].f > x) r--;
        if(l >= r) break;
        if(a[l].f + a[r].f == x){
            ans = {a[l].s+1, a[r].s+1};
        }
    }
    if(ans.f == -1){
        cout << "IMPOSSIBLE\n";
    }
    else{
        cout << ans.f << " " << ans.s << nL;
    }
    
    return 0;
}
