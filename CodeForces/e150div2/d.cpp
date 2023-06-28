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
    rep(cn, 0, nc){
        int n; cin >> n;
        vpi ints(n);
        set<int> cc;
        cc.insert(-1);
        rep(i, 0, n){
            cin >> ints[i].f >> ints[i].s;
            cc.insert(ints[i].f);
            cc.insert(ints[i].s);
        }
        unordered_map<int, int> rl;
        int cnt = 0;
        for(int i : cc){
            rl[i] = cnt++;
        }
        vvi has(cnt, vi(cnt));
        rep(i, 0, n){
            ints[i].f = rl[ints[i].f];
            ints[i].s = rl[ints[i].s];
        }
        rep(i, 0, n){
            auto [l1, r1] = ints[i];
            rep(j, 0, i){
                auto [l2, r2] = ints[j];
                if(r1 < l2 || r2 < l1) continue;
                has[min(l1, l2)][max(r1, r2)]++;
            }
        }
        vi dp(cnt), prefmax(cnt);
        rep(i, 1, cnt){
            for(int j = i; j > 0; j--){
                if(has[j][i]){
                    dp[i] = max(dp[i], prefmax[j - 1] + 1);
                }
            }
            prefmax[i] = max(prefmax[i - 1], dp[i]);
        }
        cout << (n - (2 * prefmax[cnt - 1])) << nL;
    }
    
    return 0;
}
