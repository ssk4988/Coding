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

// Suppose we play a game with a die where we roll and sum our rolls.
// We can stop any time, and the sum is our score. However, if our sum is 
// ever a multiple of 10, our score is zero, and our game is over. What 
// strategy will yield the greatest expected score? What about the same 
// game played with values other than 10?

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vd dp(100, -1);
    rep(i, 34, 40){
        dp[i] = i;
    }
    auto go = [&](int x, auto &&go) -> ld {
        auto &ans = dp[x];
        if(ans != -1) return ans;
        ans = 0;
        if(x % 10 == 0 && x > 0) return ans;
        if(x % 10 >= 4 && x % 10 <= 9 && x >= 34) return ans = x;
        rep(i, 0, 6){
            ans += go(x + i+1, go);
        }
        ans /= 6;
        return ans = max(ld(x), ans);
    };
    cout << fixed << setprecision(8) << go(0, go) << "\n";
    rep(i, 0, 50){
        cout << i << " " << go(i, go) << "\n";
    }
    
    return 0;
}
