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
    const ll ref = 0;
    ll yref = 0;
    ll sloperef = 0;
    multiset<ll> slope;
    rep(i, 0, n){
        ll x; cin >> x;
        sloperef--;
        yref += x;
        slope.insert(x);
        slope.insert(x);
        while(sz(slope) > abs(sloperef)){
            slope.erase(prev(slope.end()));
        }
    }
    ll ans = yref, cur = yref, pre = 0;
    for(ll x : slope){
        cur += (x - pre) * sloperef;
        sloperef++;
        pre = x;
        ans = min(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
