#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int N = 100000;
using a3 = array<int, 3>;
const int inf = 1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<vector<a3>> dp(N, vector<a3>(3, {-1, -1, -1}));
    vvi divs(N);
    rep(i, 2, N){
        if(sz(divs[i]) == 0){
            for(int j = i; j < N; j += i) divs[j].pb(i);
        }
    }
    rep(i, 0, 3){
        dp[1][i] = {inf, inf, inf};
        // dp[0][i][i] = 1;
    }
    auto go = [&](int n, int t, auto &&go) -> a3 {
        if(dp[n][t][0] != -1) return dp[n][t];
        dp[n][t] = {inf, inf, inf};
        pii trans = {inf, inf};
        for(int d : divs[n]){
            auto res = go(n / d, (t+1)%3, go);
            res[t] = min(res[t], n / d);
            if(pii{res[t], n/d} < trans){
                trans = pii{res[t], n/d};
                dp[n][t] = res;
            }
        }
        if(n+1<N){
            auto res = go(n+1, (t+1)%3, go);
            res[t] = min(res[t], n+1);
            if(pii{res[t], n+1} < trans){
                trans = pii{res[t], n+1};
                dp[n][t] = res;
            }
        }
    };
    
    return 0;
}
