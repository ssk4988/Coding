#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;
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
    int n, t; cin >> n >> t;
    vi r(n), c(n);
    vd p(n);
    rep(i, 0, n){
        cin >> r[i] >> c[i] >> p[i];
    }
    vector<vd> teams(t+1, vd(1 << n));
    teams[0][0] = 1;
    vector<vd> solved(t+1, vd(n));
    rep(i, 0, t+1){
        if(i){
            rep(j, 0, n){
                solved[i][j] += solved[i-1][j];
            }
        }
        rep(mask, 0, 1 << n){
            ld exsum = 0;
            rep(j, 0, n){
                if(!(mask & (1 << j)))
                    exsum += solved[i][j];
            }
            rep(j, 0, n){
                if(!(mask & (1 << j))){
                    ld prob = 0;
                    if(exsum == 0){
                        prob = ld(1) / (n - __builtin_popcount(mask));
                    }
                    else{
                        prob = solved[i][j] / exsum;
                    }
                    if(i + r[j] <= t){
                        teams[i + r[j]][mask | (1 << j)] += teams[i][mask] * prob * (1 - p[j]);
                    }
                    if(i + r[j] + c[j] <= t){
                        teams[i + r[j] + c[j]][mask | (1 << j)] += teams[i][mask] * prob * p[j];
                        solved[i + r[j] + c[j]][j] += teams[i][mask] * prob * p[j];
                    }
                }
            }
        }
    }
    rep(i, 0, n){
        cout << fixed << setprecision(8) << solved[t][i] << "\n";
    }
    
    return 0;
}
