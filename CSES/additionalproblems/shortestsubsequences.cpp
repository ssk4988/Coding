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
    vi a(n);
    rep(i, 0, n){
        if(str[i] == 'A') a[i] = 0;
        if(str[i] == 'C') a[i] = 1;
        if(str[i] == 'G') a[i] = 2;
        if(str[i] == 'T') a[i] = 3;
    }
    vi last(4, n + 1);
    vvi transition(n + 1, vi(4));
    for(int i = n; i >= 0; i--){
        rep(j, 0, 4){
            transition[i][j] = last[j];
        }
        if(i){
            last[a[i-1]] = i;
        }
    }
    vector<pair<int, pi>> dp(n + 2, {INT_MAX, {-1, -1}});
    dp[0] = {0, {0, 0}};
    rep(i, 0, n + 1){
        rep(j, 0, 4){
            int nex = transition[i][j];
            dp[nex] = min(dp[nex], {dp[i].f + 1, {i, j}});
        }
    }
    vi buildback, ans;
    buildback.pb(n + 1);
    while(buildback.back() != 0){
        auto [len, trans] = dp[buildback.back()];
        buildback.pb(trans.f);
        ans.pb(trans.s);
    }
    reverse(all(ans));
    vector<char> word = {'A', 'C', 'G', 'T'};
    rep(i, 0, sz(ans)){
        cout << word[ans[i]];
    }
    cout << nL;
    
    return 0;
}