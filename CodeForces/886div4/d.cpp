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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        sort(all(a));
        multiset<int> pre;
        pre.insert(0);
        int lef = 0;
        vi dp(n);
        rep(i, 0, n){
            while(lef < i && a[lef] + k < a[i]){
                pre.erase(pre.find(dp[lef]));
                lef++;
            }
            dp[i] = 1 + *pre.rbegin();
            pre.insert(dp[i]);
        }
        int ans = 0;
        rep(i, 0, n){
            ans = max(ans, dp[i]);
        }
        cout << (n - ans) << nL;
    }
    
    return 0;
}