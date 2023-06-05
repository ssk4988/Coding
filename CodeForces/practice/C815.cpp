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
using vvl = vector<vl>;

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
    int n; ll b;
    cin >> n >> b;
    vi par(n);
    vl c(n), d(n);
    rep(i, 0, n){
        cin >> c[i] >> d[i];
        if(i) cin >> par[i];
        par[i]--;
    }
    vector<vvl> dp(n, vvl(2));
    vi subsz(n);
    auto solve = [&](int cur, int p, auto && solve)->void{
        subsz[cur] = 1;
        for(int i : adj[cur]){
            if(i == p) continue;
            solve(i, cur, solve);
            subsz[cur] += subsz[i];
        }
        dp[cur][0].resize(subsz[cur] + 1);
        dp[cur][1].resize(subsz[cur] + 1);
        // calc for no coupon
        ll starting = 0;
        vl diffs;
        for(int i : adj[cur]){
            if(i == p) continue;
            rep(j, 0, sz())
        }
    };
    
    return 0;
}
