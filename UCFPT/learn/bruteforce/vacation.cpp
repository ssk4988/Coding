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
        int n, b; cin >> n >> b;
        vvi adj(n+1, vi(n+1, 1));
        vpi c(n);
        rep(i, 0, n){
            cin >> c[i].f >> c[i].s;
        }
        c.pb({0, 0});
        rep(i, 0, b){
            int x, y; cin >> x >> y; x--, y--;
            adj[x][y] = adj[y][x] = 0;
        }
        double ans = 1e9;
        auto go = [&](vi &used, int last, double time, auto &&go)-> void  {
            int cnt = 0;
            rep(i, 0, sz(used)){
                if(!used[i]) cnt++;
                if(!used[i] && adj[last][i]){
                    used[i] = true;
                    go(used, i, time + sqrt((c[i].f - c[last].f) * (c[i].f - c[last].f) + (c[i].s - c[last].s) * (c[i].s - c[last].s)), go);
                    used[i] = false;
                }
            }
            if(cnt == 0){
                ans = min(ans, time);
            }
        };
        vi used(n);
        go(used, n, 0, go);
        cout << "Vacation #" << (cn + 1) << ":\n";
        if(ans == 1e9){
            cout << "Jimmy should plan this vacation a different day.\n";
        }
        else{
            ans += 120 * n;
            cout << "Jimmy can finish all of the rides in " << fixed << setprecision(3) << ans << " seconds.\n";
        }
        cout << nL;
    }
    
    return 0;
}
