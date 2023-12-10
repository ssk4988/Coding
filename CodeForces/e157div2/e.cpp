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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int maxstat = 1e6 + 100;
    vvi counter(2, vi(maxstat, 0));
    vvi dp(2, vi(maxstat, -2)); // -2: uncalc -1: loss for this guy 0: draw for this guy, 1: win for this guy -3: in dfs currently
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<array<int, 3>> a(n);
        set<int> ss;
        rep(j, 0, 2){
            rep(i, 0, n){
                cin >> a[i][j];
                ss.insert(a[i][j]);
                a[i][2] = i;
            }
        }
        int m; cin >> m;
        vector<array<int, 3>> b(m);
        rep(j, 0, 2) {
            rep(i, 0, m){
                cin >> b[i][j];
                ss.insert(b[i][j]);
                b[i][2] = i;
            }
        }
        map<int, int> rl;
        rl[0] = 0;
        for(int x : ss) rl[x] = sz(rl);
        rep(i, 0, n){
            rep(j, 0, 2) a[i][j] = rl[a[i][j]];
        }
        rep(i, 0, m){
            rep(j, 0, 2) b[i][j] = rl[b[i][j]];
        }
        int maxc = sz(rl);
        sort(all(a), [](auto x, auto y) -> bool { return x[0] > y[0];});
        int pnt = 0;
        int best = 0;
        for(int i = maxc - 1; i >= 0; i--){
            counter[1][i] = best;
            while(pnt < sz(a) && a[pnt][0] >= i){
                best = max(best, a[pnt][1]);
                pnt++;
            }
        }
        sort(all(b), [](auto x, auto y) -> bool { return x[0] > y[0];});
        pnt = 0, best = 0;
        for(int i = maxc - 1; i >= 0; i--){
            counter[0][i] = best;
            while(pnt < sz(b) && b[pnt][0] >= i){
                best = max(best, b[pnt][1]);
                pnt++;
            }
        }
        rep(i, 0, maxc + 1) dp[0][i] = dp[1][i] = -2;
        dp[0][0] = dp[1][0] = -1;
        auto solve = [&](int turn, int stat, auto &&solve) -> int {
            if(dp[turn][stat] != -2){
                if(dp[turn][stat] == -3) return 0;
                return dp[turn][stat];
            }
            dp[turn][stat] = -3;
            return dp[turn][stat] = -solve(1 - turn, counter[turn][stat], solve);
        };
        int lose = 0, draw = 0, win = 0;
        rep(i, 0, n){
            int v = solve(0, a[i][1], solve);
            if(v == -1) lose++;
            else if(v == 0) draw++;
            else win++;
        }
        cout << win << " "<< draw << " " << lose << nL;
    }
    
    return 0;
}
