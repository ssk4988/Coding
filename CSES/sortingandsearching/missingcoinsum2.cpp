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
    int n; cin >> n;
    vl a(n);
    vl sum(30), mins(30, LLONG_MAX);
    rep(i, 0, n){
        cin >> a[i];
        int ob = 64-1-__builtin_clzll(a[i]);
        // cout << ob << nL;
        sum[ob] += a[i];
        mins[ob] = min(mins[ob], a[i]);
    }
    ll ans = 0;
    rep(i, 0, 30){
        if(ans < (1 << i) - 1) break;
        if(ans >= (1 << (i + 1)) - 1 || mins[i] <= ans + 1){

        }
        else break;
        ans += sum[i];
    }
    ans++;
    cout << ans << nL;
    // a.pb(0);
    // a.pb(LLONG_MAX);
    // sort(all(a));
    // ll sum = 0;
    // for(ll i : a){
    //     if(sum + 1 < i){
    //         cout << sum + 1 << nL;
    //         return 0;
    //     }
    //     sum += i;
    // }
    // cout << sum + 1 << nL;
    
    return 0;
}
