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
    string str; cin >> str;
    int n = sz(str);
    vvi dp(n/2 + 1, vi(4, 10000));
    dp[0][0] = 0;
    rep(i, 0, n/2){
        
        rep(j, 0, 4){

        }
    }
    vi changed(n);
    int ans = 0;
    rep(i, 0, n/2){
        if(changed[i] == (str[i] == str[n - 1 - i])){
            if(changed[i] && str[i + 1] == str[n - 1 - (i + 1)]);
            else changed[i] = changed[i + 1] = true;
            ans++;
        }
    }
    cout << ans << nL;
    
    return 0;
}
