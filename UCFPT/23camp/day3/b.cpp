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
    int sum = 0;
    rep(i, 0, n){
        cin >> a[i];
        sum += a[i];
    }
    int BLANK = -1;
    vvi dp(n, vi(2, BLANK));
    auto solve = [&](int idx, int token, auto && solve) -> int{
        if(dp[idx][token] != BLANK) return dp[idx][token];
        if(idx == n - 1){
            dp[idx][token] = a[idx];
        }
        else{
            dp[idx][token] = max(a[idx] - solve(idx + 1, 1 - token, solve), solve(idx + 1, token, solve) - a[idx]);
        }
        return dp[idx][token];
    };
    int bobdiff = solve(0, 1, solve);
    int alice = (sum - bobdiff) / 2;
    int bob = sum - alice;
    cout << alice << " " << bob << nL;
    
    return 0;
}