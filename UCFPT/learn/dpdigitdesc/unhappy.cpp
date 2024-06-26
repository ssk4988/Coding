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

vi loops(2000);
vi calcd(2000);

int BLANK = -1;
vector<vvl> dp;
vi str;

ll conv(ll k){
    ll res = 0;
    while(k > 0){
        res += (k % 10) * (k % 10);
        k /= 10;
    }
    return res;
}

ll solve(int dig, int runningsum, int matched){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(dig >= sz(str)){
        return loops[runningsum];
    }
    if(dp[dig][runningsum][matched] != BLANK) return dp[dig][runningsum][matched]; 
    int LIM = matched ? str[dig] : 9;
    dp[dig][runningsum][matched] = 0;
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        int newmatched = matched;
        int newrunningsum = runningsum + i * i;
        if(newmatched && i < str[dig]) newmatched = false;
        dp[dig][runningsum][matched] += solve(dig + 1, newrunningsum, newmatched);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return dp[dig][runningsum][matched];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    calcd[1] = true;
    loops[1] = false;
    calcd[0] = true;
    loops[0] = false;
    rep(i, 2, 2000){
        if(calcd[i])continue;
        set<ll> seen;
        ll cur = i;
        while(!calcd[cur] && seen.count(cur) == 0){
            seen.insert(cur);
            cur = conv(cur);
        }
        bool works = calcd[cur] ? loops[cur] : seen.count(cur);
        for(ll j : seen){
            loops[j] = works;
            calcd[j] = true;
        }
    }
    auto digtostr = [](ll v) -> vi{
        vi res;
        while(v > 0){
            res.pb(v % 10);
            v /= 10;
        }
        return res;
    };
    auto calc = [&](ll v) -> ll{
        // if(v < 0) return 0;
        // if(v == 0) return 1;
        // str.clear();
        // cout << "read digit : ";
        str = digtostr(v);
        reverse(all(str));
        // cout << nL;
        // cout << sz(str) << nL;
        dp = vector<vvl>(sz(str), vvl(2000, vl(2, BLANK)));
        ll ans = solve(0, 0, 1);
        // rep(i, 0, 1 + str.back()){
        //     ll val = solve(sz(str) - 1, i, i == str.back(), i == 0);
        //     // cout << "dig " << i << " contributes " << val << nL;
        //     ans += val;
        // }
        return ans;
    };
    
    ll a, b; 
    while(true){
        cin >> a >> b;
        if(a==0 && b==0) break;
        // cout << calc(a - 1) << nL;
        // cout << calc(b) << nL;
        cout << (calc(b) - calc(a - 1)) << nL;
    }

    
    return 0;
}
