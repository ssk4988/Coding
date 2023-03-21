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
    unordered_map<ll, int> prev;
    prev[0]++;
    int n; cin >> n;
    ll x; cin >> x;
    ll cur = 0;
    ll ans = 0;
    rep(i, 0, n){
        int v; cin >> v;
        cur += v;
        ans += prev[cur - x];
        prev[cur]++;
    }
    cout << ans << nL;
    
    return 0;
}
