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

#define maxN 5005

int palcnt[maxN][maxN];
int dp[maxN][maxN];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = str.size();
    rep(i, 0, n){
        for(int j = 0; i - j >= 0 && i + j < n && str[i-j] == str[i + j]; j++){
            palcnt[i - j][i + j] = 1;
        }
        for(int j = 0; i - j >= 0 && i + 1 + j < n && str[i-j] == str[i + 1 + j]; j++){
            palcnt[i - j][i + 1 + j] = 1;
        }
        dp[i][i] = 1;
    }
    for(int end = n - 1; end >= 0; end--){
        for(int start = end - 1; start >= 0; start--){
            palcnt[start][end] += palcnt[start+1][end];
        }
    }
    rep(i, 0, n){
        rep(j, i + 1, n){
            dp[i][j] = dp[i][j - 1] + palcnt[i][j];
        }
    }
    int q; cin >> q;
    rep(i, 0, q){
        int a, b;
        cin >> a >> b;
        a--;b--;
        cout << dp[a][b] << nL;
    }
    
    return 0;
}