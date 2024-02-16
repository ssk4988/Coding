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
    int n; ll c; cin >> n >> c;
    vl x(n);
    rep(i, 0, n){
        cin >> x[i];
    }
    ll base = x[n - 1] - x[0];
    ll ans = min(base * 2 + c, base + c * n);
    rep(i, 0, n){
        rep(j, i, n){
            ans = min(ans, (j - i + 1) * c + 2 * base - abs(x[j] - x[i]));
            if(i + 2 <= j) ans = min(ans, 3 * c + 2 * base - abs(x[j] - x[i]) + abs(x[j - 1] - x[i + 1]) * 3);
        }
    }
    cout << ans << nL;
    
    return 0;
}