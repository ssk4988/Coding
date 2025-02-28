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
vector<vector<vector<vector<vvl>>>> sand;
vector<vector<vector<vvl>>> mid;
vi str;
bool otherconstraints;
vi oc;
 
ll solve2(int start, int end, int dig, int curdigit, int matched){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(mid[start][end][dig][curdigit][matched] != BLANK) return mid[start][end][dig][curdigit][matched]; 
    if(dig == end){
        return mid[start][end][dig][curdigit][matched] = !(matched && otherconstraints && oc.back() == start - 1);
    }
    int LIM = matched ? str[dig + 1] : 9;
    mid[start][end][dig][curdigit][matched] = 0;
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        int newmatched = matched;
        if(newmatched && i < str[dig + 1]) newmatched = false;
        mid[start][end][dig][curdigit][matched] += solve2(start, end, dig + 1, i, newmatched);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return mid[start][end][dig][curdigit][matched];
}
ll solve(int start, int end, int dig, int curdigit, int matched, int allsame){
    // cout << dig << " " << curdigit << " " << matched << nL;
    if(sand[start][end][dig][curdigit][matched][allsame] != BLANK) return sand[start][end][dig][curdigit][matched][allsame]; 
    if(dig == end){
        // use other recurrence
        int otherstart = sz(str) - 1 - (end - start);
        int otherend = sz(str) - 1;
        int middlestart = end + 1;
        int middleend = otherstart - 1;
        if(middlestart > middleend) return sand[start][end][dig][curdigit][matched][allsame] = !(matched && otherconstraints && oc.back() == end);
        sand[start][end][dig][curdigit][matched][allsame] = 0;
        int LIM = matched ? str[dig + 1] : 9;
        rep(i, 0, LIM + 1){
            if(allsame && i == curdigit && (middleend - middlestart + 1) % 2 == 0) continue;
            int newmatched = matched;
            if(newmatched && i < str[dig + 1]) newmatched = false;
            sand[start][end][dig][curdigit][matched][allsame] += solve2(middlestart, middleend, dig + 1, i, newmatched);
        }
        return sand[start][end][dig][curdigit][matched][allsame];
    }
    int LIM = matched ? str[dig + 1] : 9;
    sand[start][end][dig][curdigit][matched][allsame] = 0;
    int otherind = sz(str) - 1 - (dig + 1 - start);
    // cout << "lim for below: " << LIM << nL;
    rep(i, 0, LIM + 1){
        // if(matched && i > str[otherind]) continue;
        int newmatched = matched;
        if(newmatched && i < str[dig + 1]) newmatched = false;
        sand[start][end][dig][curdigit][matched][allsame] += solve(start, end, dig + 1, i, newmatched, allsame && i == curdigit);
    }
    // cout << "dig: " << dig << " val: " << curdigit << " match: " << matched << " ans: " << dp[dig][curdigit][matched] << nL;
    return sand[start][end][dig][curdigit][matched][allsame];
}

 
int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
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
        if(v == 0) return 0;
        // str.clear();
        // cout << "read digit : ";
        str = digtostr(v);
        reverse(all(str));
        // cout << nL;
        // cout << sz(str) << nL;
        // dp = vector<vector<vvl>>(sz(str), vector<vvl>(10, vvl(2, vl(2, BLANK))));
        sand = vector<vector<vector<vector<vvl>>>>(sz(str), vector<vector<vector<vvl>>>(sz(str), vector<vector<vvl>>(sz(str), vector<vvl>(10, vvl(2, vl(2, BLANK))))));
        mid = vector<vector<vector<vvl>>>(sz(str), vector<vector<vvl>>(sz(str), vector<vvl>(sz(str), vvl(10, vl(2, BLANK)))));
        ll ans = 0;
        rep(i, 0, sz(str)){
            // otherconstraints = false;
            rep(j, i, sz(str)){
                int otherind = sz(str) - 1 - (j - i);
                if(otherind <= j) continue;
                // otherconstraints = otherconstraints || str[j] > str[otherind];
                otherconstraints = false;
                oc.clear();
                rep(d, i, j + 1){
                    int otherind1 = otherind + (d - i);
                    otherconstraints = otherconstraints || str[d] > str[otherind1];
                    if(str[d] > str[otherind1]){
                        oc.pb(d);
                    }
                }
                int LIM = i == 0 ? str[0] : 9;
                rep(d, 1, LIM + 1){
                    bool matched = i == 0 && d == str[0];
                    // if(matched && d > str[otherind]) continue;
                    ll val = solve(i, j, i, d, matched, 1);
                    // cout << "start: " << i << " end: " << j << " idx: " << i << " digit: " << d << " match: " << matched << " all same: " << 1 << " contributes: " << val << nL;
                    ans += val;
                }
            }
        }
        return ans;
        // ll ans = solve(0, 0, 1, 1);
        // rep(i, 0, 1 + str.back()){
        //     ll val = solve(sz(str) - 1, i, i == str.back(), i == 0);
        //     // cout << "dig " << i << " contributes " << val << nL;
        //     ans += val;
        // }
        // return ans - 1;
    };
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll a;
        cin >> a;
        cout << calc(a) << nL;
    }
    ll pre = 0;
    rep(i, 1, 1500){
        ll a = calc(i);
        if(a != pre){
            cout << i << " " << a << nL;
        }
        pre = a;
    }
    // cout << "999 " << calc(999) << nL;
    // cout << "1001 " << calc(1001) << nL;
    // cout << "1010 " << calc(1010) << nL;
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
