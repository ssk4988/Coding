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
    int n, q;
    cin >> n >> q;
    vl a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    vl streak(n);
    vl pref(n);
    vl starts(n);
    rep(i, 0, n)
    {
        if (i > 0)
        {
            if (a[i] <= a[i - 1])
            {
                streak[i] = streak[i - 1] + 1;
                starts[i] = starts[i - 1];
            }
            else
            {
                streak[i] = 0;
                starts[i] = i;
            }
        }
        if (streak[i] >= 2)
            pref[i]++;
        if(i>0)pref[i] += pref[i - 1];
    }
    rep(i, 0, q)
    {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        ll cur = pref[b] - (a > 0 ? pref[a - 1] : 0);
        ll ans = b - a + 1 - cur;
        rep(j, a, b + 1){
            if(streak[j] >= 2 && j - a < 2) ans++;
            if(j - a >= 2) break;
        }
        // if(abs(starts[a] - a) >= 2){
        //     cur -= min(ll(2), b - a + 1);   
        // }
        // else if(abs(starts[a] - a) == 1 && b > a){
        //     cur -= 1;
        // }
        // cur -= min(2, abs(starts[a] - a));
        // cur = max(cur, 0);
        cout << ans << nL;
    }

    return 0;
}
