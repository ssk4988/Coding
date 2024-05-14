#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, cn= 0;
    const int oo = 1e9;
    while(cin >> n){
        int m; cin >> m;
        vvi c(n, vi(n, oo));
        rep(i, 0, m){
            int u, v, w; cin >> u >> v >> w;
            if(u == 0 || u == n-2) u = n - 2 - u;
            if(v == 0 || v == n-2) v = n - 2 - v;
            c[u][v] = c[v][u] = min(c[u][v], w);
        }
        rep(i, 0, n) c[i][i] = 0;
        rep(k, 0, n){
            rep(i, 0, n){
                rep(j, 0, n) c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
            }
        }
        cout << "Case " << ++cn << ": ";
        if(n == 3){
            cout << c[n-2][0]+c[0][n-1]+c[n-1][0]+c[0][n-2] << "\n";
            continue;
        }
        n -= 2;
        vector<vvi> dps(2, vvi(1 << n, vi(n, oo)));
        rep(i, 0, n){
            dps[0][1 << i][i] = c[n][i];
            dps[1][1 << i][i] = c[n+1][i];
        }
        rep(mask, 0, 1 << n){
            rep(last, 0, n){
                rep(t, 0, 2){
                    if(dps[t][mask][last] == oo) continue;
                    rep(next, 0, n){
                        if((mask >> next) & 1) continue;
                        dps[t][mask | (1 << next)][next] = min(dps[t][mask | (1 << next)][next], dps[t][mask][last] + c[last][next]);
                    }
                }
            }
        }
        int ans = oo;
        rep(mask, 0, 1 << n){
            if(__builtin_popcount(mask) != n/2) continue;
            int forward = oo, reverse = oo;
            int omask = (1 << n) - 1;
            omask ^= mask;
            rep(l1, 0, n){
                rep(l2, 0, n){
                    forward = min(forward, dps[0][mask][l1] + dps[1][omask][l2] + c[l1][l2]);
                    reverse = min(reverse, dps[1][mask][l1] + dps[0][omask][l2] + c[l1][l2]);
                }
            }
            ans = min(ans, forward + reverse);
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
