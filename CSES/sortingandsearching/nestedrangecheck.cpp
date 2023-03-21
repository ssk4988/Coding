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


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vpi arr(n);
    vector<int> a;
    a.pb(0);
    rep(i, 0, n)
    {
        cin >> arr[i].f >> arr[i].s;
        a.pb(arr[i].f);
        a.pb(arr[i].s);
    }
    vector<int> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    vi prefs(sz(d)), prefe(sz(d));
    rep(i, 0, n){
        arr[i].f = lower_bound(all(d), arr[i].f) - d.begin();
        arr[i].s = lb(all(d), arr[i].s) - d.begin();
        prefs[arr[i].f]++;
        prefe[arr[i].s]++;
    }
    partial_sum(all(prefs), prefs.begin());
    partial_sum(all(prefe), prefe.begin());
    auto countnested = [&](int l, int r) -> int{
        return prefe[r] - prefs[l - 1];
    };
    rep(i, 0, n){
        cout << (countnested(arr[i].f, arr[i].s) > 1 ? 1 : 0) << " ";
    }
    cout << "\n";
    rep(i, 0, n){
        cout << (prefs[arr[i].f] - (prefe[arr[i].s - 1] - countnested(arr[i].f + 1, arr[i].s - 1)) > 1 ? 1 : 0) << " ";
    }
    cout << "\n";

    return 0;
}
