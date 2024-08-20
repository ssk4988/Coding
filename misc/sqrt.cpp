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
    int LIM = 1e6;
    vi dp(LIM, 1e9);
    dp[0] = 0;
    auto cost = [&](int i) { return i * (i + 1) / 2; };
    int i = 1;
    for(; cost(i) < LIM; i++) {
        for(int j = 0; j + cost(i) < LIM; j++) {
            dp[j + cost(i)] = min(dp[j + cost(i)], 1 + i + dp[j]);
        }
    }
    for(int i = 1; i < LIM; i++) {
        dp[i] -= 1;
    }
    vi greedy(LIM);
    for(int i = 1; i < LIM; i++) {
        greedy[i] = -1;
        int c = i;
        for(int j = 1e3; j > 0; j--) {
            while(cost(j) <= c) greedy[i] += 1 + j, c -= cost(j);
        }
    }
    int mx = 0, mn = 0;
    for(int i = 1; i < LIM; i++) {
        if(greedy[i] != dp[i]){
            cout << i << " " << greedy[i] << " " << dp[i] << "\n";
            mx = max(mx, greedy[i] - dp[i]);
            mn = min(mn, greedy[i] - dp[i]);
        }
    }
    cout << mn << " " << mx << endl;
    
    return 0;
}