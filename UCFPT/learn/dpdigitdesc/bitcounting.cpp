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

int base = 2;

vi kval(80);

int BLANK = -1;
vector<vvl> dp;
vi str;

int ktarget;
ll solve(int dig, int num1s, int matched){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(dig >= sz(str)){
        return ktarget == 1 + kval[num1s];
    }
    if(dp[dig][num1s][matched] != BLANK) return dp[dig][num1s][matched]; 
    int LIM = matched ? str[dig] : base - 1;
    dp[dig][num1s][matched] = 0;
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        int newmatched = matched;
        int newnum1s = num1s + (i == 1);
        if(newmatched && i < str[dig]) newmatched = false;
        dp[dig][num1s][matched] += solve(dig + 1, newnum1s, newmatched);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return dp[dig][num1s][matched];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    kval[0] = -1;
    kval[1] = 0;
    rep(i, 2, 80){
        int num1s = 0;
        int i2 = i;
        while(i2 > 0){
            if(i2 & 1) num1s++;
            i2>>=1;
        }
        kval[i] = 1 + kval[num1s];
    }
    auto digtostr = [](ll v) -> vi{
        vi res;
        while(v > 0){
            res.pb(v % base);
            v /= base;
        }
        return res;
    };
    auto calc = [&](ll v) -> ll{
        if(ktarget == 0) return v >= 1;
        // if(v < 0) return 0;
        // if(v == 0) return 1;
        // str.clear();
        // cout << "read digit : ";
        str = digtostr(v);
        reverse(all(str));
        // cout << nL;
        // cout << sz(str) << nL;
        dp = vector<vvl>(sz(str), vvl(80, vl(2, BLANK)));
        ll ans = solve(0, 0, 1);
        // rep(i, 0, 1 + str.back()){
        //     ll val = solve(sz(str) - 1, i, i == str.back(), i == 0);
        //     // cout << "dig " << i << " contributes " << val << nL;
        //     ans += val;
        // }
        return ans - (ktarget == 1 && v >= 1);
    };
    // what about n0 = 1
    ll a, b; 
    while(true){
        cin >> a >> b >> ktarget;
        if(a==0 && b==0 && ktarget == 0) break;
        // cout << calc(a - 1) << nL;
        // cout << calc(b) << nL;
        cout << (calc(b) - calc(a - 1)) << nL;
    }

    
    return 0;
}
