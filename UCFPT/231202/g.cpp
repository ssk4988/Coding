#include <bits/stdc++.h>
using namespace std;

using l = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<l, l>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<l>;
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
    int n = sz(str);
    vvi dp(n, vi(n));
    rep(keylen, 1, n + 1){
        if(n % keylen != 0) continue;
        vector<string> ans;
        rep(start, 0, n - keylen + 1){
            string s1 = str.substr(start, keylen);
            rep(i, 0, n){
                rep(j, i, n) dp[i][j] = 0;
                if(i + keylen - 1 < n && s1 == str.substr(i, keylen)) {
                    dp[i][i + keylen - 1] = 1;
                }
            }
            rep(len, 1, n + 1){
                if(len == keylen) continue;
                int idx = ((len % keylen) - 1 + keylen) % keylen;
                rep(i, 0, n - len + 1){
                    int j = i + len - 1;
                    if(str[j] == s1[idx] && (len == 1 || dp[i][j-1])) dp[i][j] = true;
                    // !dp[i][j]
                    for(int len1 = keylen; len1 < len; len1 += keylen){
                        if(dp[i][i + len1 - 1] && dp[i + len1][j]) dp[i][j] = true;
                        if(dp[j - len1 + 1][j] && dp[i][j - len1]) dp[i][j] = true;
                    }
                }
            }
            if(dp[0][n-1]){
                ans.push_back(s1);
            }
        }
        if(sz(ans)){
            sort(all(ans));
            cout << ans[0] << "\n";
            return 0;
        }
    }
    
    return 0;
}
