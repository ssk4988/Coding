#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)

using p = array<ll, 3>;
int n;
p m;
vector<vector<p>> ps;
vector<p> ss;

vector<vector<double>> dp, ecost;
vector<double> ordist;
int np;

inline double calc(p a, p b){
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]));
}

double solve(int mask, int prev){
    if(dp[mask][prev] != -1) return dp[mask][prev];
    if(__builtin_popcount(mask) == 1){
        dp[mask][prev] = ordist[prev];
        return dp[mask][prev];
    }
    double &res = dp[mask][prev];
    res = DBL_MAX;
    rep(i, 0, np){
        if(i == prev) continue;
        if((mask >> i) & 1){
            res = min(res, solve(mask ^ (1 << prev), i) + ecost[i][prev]);
        }
    }
    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    p m;
    while(true){
        cin >> n >> m[0] >> m[1] >> m[2];
        if(n == 0) break;
        ps = vector<vector<p>>(n);
        ss = vector<p>(n);
        rep(i, 0, n){
            int k; cin >> k; cin >> ss[i][0] >> ss[i][1] >> ss[i][2];
            ps[i].resize(k);
            rep(j, 0, k){
                cin >> ps[i][j][0] >> ps[i][j][1] >> ps[i][j][2];
            }
        }
        vector<vector<double>> adj(n, vector<double>(n));
        vector<vector<double>> cost(n);
        rep(s1, 0, n){
            np = sz(ps[s1]);
            ordist = vector<double>(np);
            dp = vector<vector<double>>(1 << np, vector<double>(np, -1));
            ecost = vector<vector<double>>(np, vector<double>(np));
            rep(i, 0, np){
                ordist[i] = calc(ss[s1], ps[s1][i]);
                rep(j, 0, np){
                    ecost[i][j] = calc(ps[s1][i], ps[s1][j]);
                }
            }
            rep(i, 0, np){
                cost[s1].push_back(solve((1 << np) - 1, i));
            }
            rep(s2, 0, n){
                if(s1 == s2) continue;
                adj[s1][s2] = DBL_MAX;
                rep(i, 0, np){
                    adj[s1][s2] = min(adj[s1][s2], cost[s1][i] + calc(ss[s2], ps[s1][i]));
                }
            }
        }
        np = n;
        ordist = vector<double>(np);
        dp = vector<vector<double>>(1 << np, vector<double>(np, -1));
        ecost = adj;
        rep(i, 0, n){
            ordist[i] = calc(ss[i], m);
        }
        double ans = DBL_MAX;
        rep(i, 0, np){
            double cur = solve((1 << np) - 1, i);
            rep(j, 0, sz(ps[i])){
                ans = min(ans, cur + cost[i][j]);
            }
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }

    return 0;
}