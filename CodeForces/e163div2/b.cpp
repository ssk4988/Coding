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
        int n; cin >> n;
        vector<string> v(n);
        rep(i, 0, n){
            cin >> v[i];
        }
        vvi dp(n, vi(2));
        dp[0][1] = true;
        {
            string v1 = v[0];
            sort(all(v1));
            dp[0][0] = v1 == v[0];
        }
        rep(i, 1, n){
            if(stoi(v[i]) >= stoi(v[i-1]) && dp[i-1][1]){
                dp[i][1] = true;
            }
            if(stoi(v[i]) >= stoi(v[i-1].substr(sz(v[i-1]) - 1, 1)) && dp[i-1][0]){
                dp[i][1] = true;
            }
            string v1 = v[i];
            sort(all(v1));
            if(v1 != v[i]) continue;
            if(stoi(v[i].substr(0, 1)) >= stoi(v[i-1]) && dp[i-1][1]){
                dp[i][0] = true;
            }
            if(stoi(v[i].substr(0, 1)) >= stoi(v[i-1].substr(sz(v[i-1]) - 1, 1)) && dp[i-1][0]){
                dp[i][0] = true;
            }
        }
        cout << (dp[n-1][0] || dp[n-1][1] ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
