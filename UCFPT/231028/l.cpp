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

using a4 = array<int, 4>;

ld dp[1 << 15][2][51][15]; // word 50 is choose next word and state
int n; map<string, int> rl;
vi t;
a4 ft = {};
a4 tmasks = {};
int m;
vi hmasks;
vector<a4> hfreq;
ld eps = 1e-9;
ld solve(int mask, int turn, int word, int left){
    // cout << "trying " << mask << " " << turn << " " << word << " " << left << "\n";
    if(dp[mask][turn][word][left] > -eps) return dp[mask][turn][word][left];
    // terminal states
    if(mask & tmasks[3]){
        // cout << "assassin pulled\n";
        return dp[mask][turn][word][left] = 0; // we lose if we pulled the assassin
    }
    if(__builtin_popcount(mask & tmasks[0]) == ft[0] || __builtin_popcount(mask & tmasks[1]) == ft[1]){
        int winner = __builtin_popcount(mask & tmasks[1]) == ft[1];
        // cout << "BR"[winner] << " won\n";
        return dp[mask][turn][word][left] = turn == winner; // if we won then 1 otherwise 0
    }
    dp[mask][turn][word][left] = 0;
    if(word == 50){
        // choose next state
        rep(w, 0, m){
            rep(l, 1, 1 + __builtin_popcount((~mask) & hmasks[w])){
                ld v = solve(mask, turn, w, l);
                // cout << "trying combo " << w << " " << l << " on state " << mask << " " << turn << " which is " << v << "\n";
                dp[mask][turn][word][left] = max(dp[mask][turn][word][left], v);
            }
        }
    }
    else if(left == 0){
        // change turns
        dp[mask][turn][word][left] = 1 - solve(mask, turn ^ 1, 50, 0);
    }
    else{
        dp[mask][turn][word][left] = 0;
        // choose next word
        for(int leftmask = (~mask) & hmasks[word], st = 0, numleft = __builtin_popcount(leftmask); leftmask; leftmask >>= 1, st++){
            if(leftmask & 1){
                if(t[st] == 2 || t[st] == 1 - turn){
                    // stop turn due to innocent / other
                    dp[mask][turn][word][left] += (1 - solve(mask ^ (1 << st), turn ^ 1, 50, 0)) / numleft;
                }
                else dp[mask][turn][word][left] += 1 / ld(numleft) * solve(mask ^ (1 << st), turn, word, left-1);
            }
        }

    }
    // assert(dp[mask][turn][word][left] != -1);
    // cout << "dp: " << mask << " " << turn << " " << word << " " << left << " = " << dp[mask][turn][word][left] << "\n";
    return dp[mask][turn][word][left];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    string ustr; cin >> ustr;
    // 0 blue 1 red
    int us = ustr == "R";
    
    rep(i, 0, n){
        string str; cin >> str;
        rl[str] = i;
    }
    t = vi(n); 
    rep(i, 0, n){
        string ts; cin >> ts;
        if(ts == "B") t[i] = 0;
        else if(ts == "R") t[i] = 1;
        else if(ts == "I") t[i] = 2;
        else t[i] = 3;
        ft[t[i]]++;
        tmasks[t[i]] ^= 1 << i;
    }
    cin >> m;
    hmasks.resize(m);
    hfreq.resize(m);
    rep(i, 0, m){
        int k; cin >> k;
        rep(j, 0, k){
            string str; cin >> str;
            int v = rl[str];
            hfreq[i][t[v]]++;
            hmasks[i] ^= 1 << v;
        }
    }
    int b = 1 << n;
    memset(dp, -1, sizeof dp);
    // rep(i, 0, b){
    //     bool assassin = (i & tmasks[3]) > 0;
    //     bool otherwin = __builtin_popcount(i & tmasks[0]) == ft[0] || __builtin_popcount(i & tmasks[1]) == ft[1];
    //     if(!assassin && !otherwin) continue;
    //     rep(j, 0, 2){
    //         rep(k, 0, 51){
    //             rep(l, 0, 15){
    //                 if(assassin) dp[i][j][k][l] = 0;
    //                 else dp[i][j][k][l] = (__builtin_popcount(i & tmasks[1]) == ft[1]) == j;
    //             }
    //         }
    //     }
    // }
    ld ans = solve(0, us, 50, 0);
    cout << fixed << setprecision(5) << ans << "\n";
    
    return 0;
}
