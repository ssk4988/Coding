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
    int n, m;
    cin >> n >> m;
    int a[n];
    int b[m];
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    rep(i, 0, m)
    {
        cin >> b[i];
    }
    sort(a, a + n);
    sort(b, b + m);
    int l = 0;
    int r = 0;
    int ans = 0;
    rep(i, 0, n)
    {
        while (l + 1 < m && b[l + 1] <= a[i])
        {
            l++;
        }
        while (r + 1 < m && b[r] < a[i])
        {
            r++;
        }
        ans = max(ans, min(abs(b[l] - a[i]), abs(b[r] - a[i])));
    }
    cout << ans << nL;

    return 0;
}