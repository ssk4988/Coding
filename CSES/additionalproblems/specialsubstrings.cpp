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
    string str; cin >> str;
    vi frq(26);
    map<vi, ll> mm;
    vi frq1(26, -1);
    rep(i, 0, sz(str)) frq1[str[i] - 'a'] = 0;
    mm[frq1]++;

    rep(i, 0, sz(str)){
        frq[str[i] - 'a']++;
        vi a(26, -1);
        int mn = INT_MAX;
        rep(j, 0, 26) if(frq1[j] != -1) mn = min(mn, frq[j]);
        rep(j, 0, 26) if(frq1[j] != -1) a[j] = frq[j] - mn;
        mm[a]++;
    }
    ll ans = 0;
    for(auto [key, val] : mm){
        ans += (val - 1) * val / 2;
    }
    cout << ans << nL;

    return 0;
}