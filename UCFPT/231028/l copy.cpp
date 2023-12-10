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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string ustr; cin >> ustr;
    // 0 blue 1 red
    int us = ustr == "R";
    map<string, int> rl;
    rep(i, 0, n){
        string str; cin >> str;
        rl[str] = i;
    }
    vi t(n);
    a4 ft = {};
    rep(i, 0, n){
        string ts; cin >> ts;
        if(ts == "B") t[i] = 2;
        else if(ts == "R") t[i] = 3;
        else if(ts == "I") t[i] = 1;
        else t[i] = 0;
        ft[t[i]]++;
        // cout << i << " " << t[i] << "\n";
    }
    int m; cin >> m;
    vi hmasks(m);
    vector<a4> hfreq(m);
    vector<vl> ways(m, vl(2));
    vl fact(20);
    fact[0] = 1;
    rep(i, 1, sz(fact)) fact[i] = fact[i-1] * i;
    rep(i, 0, m){
        int k; cin >> k;
        rep(j, 0, k){
            string str; cin >> str;
            int v = rl[str];
            hfreq[i][t[v]]++;
            hmasks[i] ^= 1 << v;
        }
        rep(j, 0, 2){
            rep(k, 0, 1+hfreq[i][2 + j]) ways[i][j] += fact[k];
            ways[i][j] *= (hfreq[i][0] + hfreq[i][1] + hfreq[i][2 + 1 - j]);
        }
    }
    int b = 1 << n;
    vvi submasks(b);
    vector<vector<vector<pair<int, a4>>>> trans(b, vector<vector<pair<int, a4>>>(2));
    vector<a4> maskfreq(b);
    rep(mask, 0, b){
        vi ons;
        rep(j, 0, n){
            if((mask >> j) & 1){
                ons.pb(j);
                maskfreq[mask][t[j]]++;
            }
        }
        rep(j, 1, 1 << sz(ons)){
            int submask = 0;
            rep(k, 0, sz(ons)) if((j >> k) & 1) {
                submask ^= 1 << ons[k];
            }
            a4 &freq = maskfreq[submask];
            rep(k, 0, 2){
                int bad = freq[0] + freq[1] + freq[2 + 1 - k];
                if(bad > 1) continue; // not a valid trans
                trans[mask][k].pb({submask, freq});
                // cout << mask << " " << k << " has valid submask " << submask << "\n";
            }
        }
    }
    auto ncr = [&](int n, int r)-> ll {
        // assert(n >= r && r >= 0);
        return fact[n] / fact[r] / fact[n - r];
    };
    auto npr = [&](int n, int r)-> ll {
        // assert(n >= r && r >= 0);
        return fact[n] / fact[n-r];
    };
    vector<vd> dp(b, vd(2, -1));
    rep(i, 0, b){
        a4 freq = {};
        rep(j, 0, n){
            if((i >> j) & 1){
                freq[t[j]]++;
            }
        }
        bool redwin = freq[3] == ft[3], bluewin = freq[2] == ft[2], apick = freq[0] == ft[0];
        if(redwin + bluewin + apick != 1) continue;
        rep(j, 0, 2){
            // cout << i << " " << j << " is a terminal state\n";
            if(redwin){
                dp[i][j] = j == 1;
            }
            else if(bluewin) dp[i][j] = j == 0;
            else dp[i][j] = 1;
        }
    }
    int allmask = b-1;
    auto solve = [&](int mask, int turn, auto && solve) -> ld {
        if(dp[mask][turn] != -1) return dp[mask][turn];
        // cout << "need to calc " << mask << " " << turn << "\n";
        dp[mask][turn] = 0;
        vector<vd> res(m, vd(n + 1));
        a4 &freq = maskfreq[mask];
        rep(i, 0, m){
            a4 &leftfreq = maskfreq[hmasks[i] & (allmask ^ mask)];
            int wordsleft = leftfreq[0] + leftfreq[1] + leftfreq[2] + leftfreq[3];
            for(auto [submask, sfreq] : trans[allmask ^ mask][turn]){
                if((hmasks[i] & submask) != submask) continue; // not a submask of hint
                if((sfreq[2] + freq[2] == ft[2]) + (sfreq[3] + freq[3] == ft[3]) + (sfreq[0] + freq[0] > 0) + (sfreq[1] > 0) > 1) continue;
                int uscnt = sfreq[2 + turn], badcnt = sfreq[0] + sfreq[1] + sfreq[2 + 1 - turn];
                ld prb = ld(1) / ncr(wordsleft, uscnt);
                if(badcnt) prb /= (wordsleft - uscnt);
                // cout << mask << " "<< turn << " trans with word " << i << " and mask " << submask << " with prb=" << prb << "\n";
                int ons = __builtin_popcount(submask);
                int lim = badcnt ? n + 1 : 1 + ons;
                rep(j, ons, lim)
                    res[i][j] += prb * (1 - solve(mask ^ submask, turn ^ 1, solve));
            }
        }
        rep(i, 0, m) {
            rep(j, 0, sz(res[i])){
                dp[mask][turn] = max(dp[mask][turn], res[i][j]);
            }
        }
        
        // cout << "calcd " << mask << " " << turn << ":" << dp[mask][turn] << "\n";
        // rep(i, 0, m) cout << "with word " << i << ": " << res[i] << "\n";
        return dp[mask][turn];
    };
    cout << fixed << setprecision(5) << solve(0, us, solve) << "\n";
    
    return 0;
}
