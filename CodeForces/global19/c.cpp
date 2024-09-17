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

void solve()
{
    int n;
    cin >> n;
    vl a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    if(n == 3 && (a[1] & 1)) {
        cout << "-1\n";
        return;
    }
    ll ans = 0;
    bool allones = true;
    rep(i, 1, n - 1)
    {
        if(a[i] != 1) allones = false;
        ans += a[i];
        ans += a[i] & 1;
    }
    if(allones){
        cout << "-1\n";
        return;
    }
    cout << ans/2 << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc) solve();

    return 0;
}
