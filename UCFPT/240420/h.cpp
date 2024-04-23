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
const int inf = 1e9;
using a5 = array<int, 5>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int d; cin >> d;
    vi rolls(d);
    rep(i, 0, d) {cin >> rolls[i]; rolls[i]--;}
    vvi dp(d+1, vi(14, -1));
    auto score = [&](a5 &dice, int turn)->int {
        //todo
        vi freq(6);
        for(auto x : dice) freq[x]++;
        if(turn < 6){
            return freq[turn] * (turn + 1);
        }
        int bestrun = 0, currun = 0, sum = 0;
        rep(i, 0, 6){
            if(freq[i]) currun++;
            else currun = 0;
            bestrun = max(bestrun, currun);
            sum += freq[i] * (i + 1);
        }
        sort(all(freq));
        if(turn == 6){
            if(freq.back() >= 3) return sum;
            else return 0;
        }
        if(turn == 7){
            return freq.back() >= 4 ? sum : 0;
        }
        if(turn == 8) return freq.back() == 3 && freq[sz(freq) - 2] == 2 ? 25 : 0;
        if(turn == 9) return bestrun >= 4 ? 30 : 0;
        if(turn == 10) return bestrun >= 5 ? 40 : 0;
        if(turn == 11) return sum;
        if(turn == 12) return freq.back() >= 5 ? 50 : 0;
        return 1e9;
    };
    auto go = [&](int dice, int turn, auto &&go) -> int {
        if(dice > d || turn > 13) return -inf;
        auto &ans = dp[dice][turn];
        if(ans != -1) return ans;
        if(turn == 13) return ans = 0;
        ans = -inf;
        if(dice == d) return ans;
        vector<pair<a5, int>> poss;
        auto reroll = [&](int left, int curdice, a5 cur, auto &&reroll) -> void {
            if(left == 0){
                poss.push_back({cur, curdice});
                return;
            }
            rep(mask, 0, 1 << 5){
                a5 nex(cur);
                int nexdice = curdice;
                bool valid = true;
                rep(i, 0, 5){
                    if((mask >> i) & 1){
                        if(nexdice >= d) {
                            valid = false;
                            break;
                        }
                        nex[i] = rolls[nexdice++];
                    }
                }
                if(valid){
                    reroll(left-1, nexdice, nex, reroll);
                }
            }
        };
        if(dice + 5 > d) return ans;
        a5 curdice;
        rep(i, 0, 5) curdice[i] = rolls[dice + i];
        reroll(2, dice + 5, curdice, reroll);
        for(auto [p, nexdice] : poss){
            ans = max(ans, score(p, turn) + go(nexdice, turn + 1, go));
        }
        return ans;
    };
    cout << go(0, 0, go) << "\n";
    
    return 0;
}
