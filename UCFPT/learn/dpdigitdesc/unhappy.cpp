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
        dp[dig][curdigit][matched] += solve(dig + 1, newrunningsum, newmatched);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return dp[dig][curdigit][matched][rising];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    calcd[1] = true;
    loops[1] = false;
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
    
    return 0;
}
