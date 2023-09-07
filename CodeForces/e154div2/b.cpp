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
        string str1, str2; cin >> str1 >> str2;
        int n= sz(str1);
        vi dp(n + 1);
        dp[0] = true;
        rep(i, 1, n + 1){
            rep(j, 1, i + 1){
                if(dp[j - 1] && str1[j-1] == str2[j-1] && str1[i-1] == str2[i-1] && str1[j - 1] == str1[i - 1]){
                    dp[i] = true;
                }
            }
        }
        cout << (dp.back() ? "YES" : "NO") << nL;
    }
    
    return 0;
}