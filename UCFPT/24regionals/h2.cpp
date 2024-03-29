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
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    a.insert(a.begin(), 0);
    a.pb(0);
    n += 2;
    vi a2(a);
    sort(all(a2));
    a2.erase(unique(all(a2)), a2.end());
    rep(i, 0, n){
        a[i] = lower_bound(all(a2), a[i]) - a2.begin();
    }
    vector<vvi> dp(n + 1, vvi(n + 1, vi(2, -1)));
    // c is 1 means range already set matches a[l]
    auto go = [&](int l, int r, int c, auto &&go) -> int {
        int &ans = dp[l][r][c];
        if(ans != -1) return ans;
        ans = 1e9;
        if(l == r) return ans = 0;
        if(c) return ans = go(l+1, r, a[l+1] == a[l], go);
        else{
            rep(r1, l+1, r+1){
                ans = min(ans, 1 + go(l, r1, 1, go) + go(r1, r, a[r1] != a[l], go));
            }
        }
        return ans;
    };
    cout << go(0, n, 1, go) << "\n";
    
    return 0;
}
