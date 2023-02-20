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
    ll k, s;
    cin >> n >> s >> k;
    s *= 2;
    k *= 2;
    vl a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
        a[i] *= 2;
    }
    sort(all(a));

    rep(i, 0, n - 1)
    {
        if (a[i + 1] - a[i] < s)
        {
            cout << -1 << nL;
            return 0;
        }
    }
    ll ans = 0;
    vl ext(n, k / 2);
    rep(i, 0, n){
        if(i > 0){
            ext[i] = min(ext[i], a[i] - (a[i - 1] + ext[i - 1]));
        }
        if(i + 1 < n){
            ext[i] = min(ext[i], a[i + 1] - s/2 - a[i]);
        }
        ans += 2 * ext[i];
    }
    cout << ans/2 << nL;

    return 0;
}
