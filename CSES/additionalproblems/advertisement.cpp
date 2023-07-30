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
    rep(i, 0, n) cin >> a[i];
    set<int> ss;
    unordered_map<int, vi> occ;
    rep(i, 0, n){
        ss.insert(a[i]);
        occ[a[i]].pb(i);
    }
    vi vals;
    for(int i : ss) vals.pb(i);
    
    // sort(all(a));
    ll ans = n * vals[0];
    set<int> separators;
    multiset<ll> ints;
    ints.insert(n);
    separators.insert(-1);
    separators.insert(n);
    rep(i, 0, sz(vals) - 1){
        for(int j : occ[vals[i]]){
            // if(pre != -1 || i == 0) maxinterval = max(maxinterval, j - pre - 1);
            // pre = j;
            int left = *prev(separators.lower_bound(j));
            int right = *separators.upper_bound(j);
            ints.erase(ints.find(right - left - 1));
            ints.insert(j - left - 1);
            ints.insert(right - j - 1);
            separators.insert(j);
        }
        ans = max(ans, vals[i + 1] * *(ints.rbegin()));
    }
    cout << ans << nL;
    
    return 0;
}