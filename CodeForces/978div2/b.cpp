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

void solve() {
    int n , x; cin >> n >> x;
    vl a(n);
    ll sum = 0;
    rep(i, 0, n){
        cin >> a[i];
        sum += a[i];
    }
    sort(all(a));
    ll ans = max((sum + x-1) / x, a.back());

    // reverse(all(a));
    // if(n <= x){
    //     cout << a[0] << "\n";
    //     return;
    // }
    // while(sz(a) > x) {

    // }
    // ll ans = 0;
    // while(sz(pq) > x){
    //     ll y = pq.top(); pq.pop();
    //     ll z = pq.top(); pq.pop();
    //     pq.push(y + z);
    // }
    // ll mx = 0;
    // while(sz(pq)){
    //     mx = max(mx, pq.top()); pq.pop();
    // }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
