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
using vvl = vector<vl>;

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

int BLANK = -1;
vector<vector<vvl>> dp;
vi str;

ll solve(int dig, int curdigit, int matched, int leadingzeros){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(dp[dig][curdigit][matched][leadingzeros] != BLANK) return dp[dig][curdigit][matched][leadingzeros]; 
    if(dig == 0){
        dp[dig][curdigit][matched][leadingzeros] = !matched || curdigit <= str[dig];
        return dp[dig][curdigit][matched][leadingzeros];
    }
    int LIM = matched ? str[dig - 1] : 9;
    dp[dig][curdigit][matched][leadingzeros] = 0;
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        if(i == curdigit && !(leadingzeros)) continue;
        int newmatched = matched;
        int newleadingzeros = leadingzeros;
        if(leadingzeros && i != 0) newleadingzeros = false;
        if(newmatched && i < str[dig - 1]) newmatched = false;
        dp[dig][curdigit][matched][leadingzeros] += solve(dig - 1, i, newmatched, newleadingzeros);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return dp[dig][curdigit][matched][leadingzeros];
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll a, b;
    cin >> a >> b;
    auto calc = [](ll v) -> ll{
        if(v < 0) return 0;
        if(v == 0) return 1;
        str.clear();
        // cout << "read digit : ";
        while(v > 0){
            str.pb(v % 10);
            // cout << str.back();
            v /= 10;
        }
        // cout << nL;
        // cout << sz(str) << nL;
        dp = vector<vector<vvl>>(sz(str), vector<vvl>(10, vvl(2, vl(2, BLANK))));
        ll ans = 0;
        rep(i, 0, 1 + str.back()){
            ll val = solve(sz(str) - 1, i, i == str.back(), i == 0);
            // cout << "dig " << i << " contributes " << val << nL;
            ans += val;
        }
        return ans;
    };
    // cout << calc(20) << nL;
    // ll pre = 0;
    // rep(i, 0, 350){
    //     ll val = calc(i);
    //     if(val == pre){
    //         cout << i << " " << val << nL;
    //     }
    //     pre = val;
    // }
    // calc(19);
    // calc(18);
    ll b1 = calc(b);
    ll a1 = calc(a - 1);
    // cout << b1 << " " << a1 << nL;
    cout << (b1 - a1) << nL;

    
    return 0;
}