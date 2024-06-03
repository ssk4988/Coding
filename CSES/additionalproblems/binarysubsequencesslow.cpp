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
    map<pi, int> dp;
    dp[{2, 1}] = 2;
    const int oo = 1e9;
    auto go = [&](int a, int b, auto &&go) -> int {
        if(a == b) return oo;
        if(a < b) return go(b, a, go);
        if(b == 0) return a;
        // if(a == b+1 && b > 1) return oo;
        int c = a % (b+1);
        if(dp.count({a, b})) return dp[{a, b}];
        dp[{a, b}] = (a - c) / (b+1) + go(b, c, go);
        if(a == 681486 || a == 429469 || a == 252016)
        cout << a << " " << b << " " << dp[{a, b}] << "\n";
        return dp[{a, b}];
    };
    int n; cin >> n;
    pi best = {n, 0};
    for(int i = n; i > n-i; i--){
        if(go(i, n-i, go) < go(best.f, best.s, go)) best = {i, n-i};
    }
    int cur = 0;
    while(best.f != 0){
        int c = best.f % (best.s+1);
        int d = (best.f - c) / (best.s+1);
        rep(i, 0, d) cout << cur;
        cur = 1 - cur;
        best.f = c;
        if(best.f < best.s) swap(best.f, best.s);
    }
    cout << "\n";
    
    return 0;
}
