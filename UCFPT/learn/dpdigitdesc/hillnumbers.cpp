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
 
ll solve(int dig, int curdigit, int matched, int rising){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(dig >= sz(str)){
        return 1;
    }
    if(dp[dig][curdigit][matched][rising] != BLANK) return dp[dig][curdigit][matched][rising]; 
    int LIM = matched ? str[dig] : 9;
    dp[dig][curdigit][matched][rising] = 0;
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        if(!rising && i > curdigit) continue;
        int newmatched = matched;
        int newrising = rising;
        if(newrising && i < curdigit) newrising = false;
        if(newmatched && i < str[dig]) newmatched = false;
        dp[dig][curdigit][matched][rising] += solve(dig + 1, i, newmatched, newrising);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return dp[dig][curdigit][matched][rising];
}
 
int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll a;
    cin >> a;
    auto digtostr = [](ll v) -> vi{
        vi res;
        while(v > 0){
            res.pb(v % 10);
            v /= 10;
        }
        return res;
    };
    auto calc = [&](ll v) -> ll{
        if(v < 0) return 0;
        if(v == 0) return 1;
        // str.clear();
        // cout << "read digit : ";
        str = digtostr(v);
        reverse(all(str));
        // cout << nL;
        // cout << sz(str) << nL;
        dp = vector<vector<vvl>>(sz(str), vector<vvl>(10, vvl(2, vl(2, BLANK))));
        ll ans = solve(0, 0, 1, 1);
        // rep(i, 0, 1 + str.back()){
        //     ll val = solve(sz(str) - 1, i, i == str.back(), i == 0);
        //     // cout << "dig " << i << " contributes " << val << nL;
        //     ans += val;
        // }
        return ans - 1;
    };
    auto hill = [&](ll v) -> bool{
        vi digs = digtostr(v);
        bool rising = true;
        rep(i, 1, sz(digs)){
            if(rising && digs[i] < digs[i - 1]){
                rising = false;
            }
            else if(!rising && digs[i] > digs[i - 1]) return false;
        }
        return true;
    };
    if(hill(a)){
        cout << calc(a) << nL;
    }
    else{
        cout << "-1\n";
    }
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
    // // calc(18);
    // ll b1 = calc(b);
    // ll a1 = calc(a - 1);
    // // cout << b1 << " " << a1 << nL;
    // cout << (b1 - a1) << nL;
 
    
    return 0;
}
