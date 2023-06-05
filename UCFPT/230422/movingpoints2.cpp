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
using vvd = vector<vd>;

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
ld eps = 1e-4L;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, c; 
    while(true){
        cin >> n >> c;
        if(n == 0 && c == 0) break;
        vvd pos(n, vd(2)), dir(n, vd(2));
        rep(i, 0, n){
            rep(j, 0, 2) cin >> pos[i][j];
            ld d, s; cin >> d >> s;
            ld rad = d * acosl(-1L) / 180;
            dir[i][0] = s * cos(rad), dir[i][1] = s * sin(rad);
        }
        vvd dp(1 << n, vd(n, 1e18L));
        // dp[0] = {0, 0, 0}; 
        rep(i, 0, n){
            dp[0][i] = 0;
        } 
        rep(i, 0, sz(dp)){
            rep(k, 0, n){
                if(i != 0 && (i & (1 << k)) == 0) continue;
                rep(j, 0, n){
                    if((i >> j) & 1){} else{
                        int newmask = i | (1 << j);
                        ld lo = dp[i][k], hi = ld(1e18L);
                        ld curx = pos[k][0] + lo * dir[k][0], cury = pos[k][1] + lo * dir[k][1];
                        if(i == 0){
                            curx = 0, cury = 0;
                        }
                        while(fabs(hi - lo) > eps){
                            ld mid = (lo + hi) / 2;
                            ld x1 = pos[j][0] + mid * dir[j][0], y1 = pos[j][1] + mid * dir[j][1];
                            if(sqrtl((x1 - curx) * (x1 - curx) + (y1 - cury) * (y1 - cury)) <= (mid - dp[i][k]) * c){
                                hi = mid;
                            }
                            else{
                                lo = mid;
                            }
                        }
                        dp[newmask][j] = min(dp[newmask][j], lo);
                        
                    }
                }
            }
        }
        ld best = 1e18;
        rep(i, 0, n){
            best = min(best, dp.back()[i]);
        }
        cout << fixed << setprecision(2) << best << nL;

    }
    
    return 0;
}
