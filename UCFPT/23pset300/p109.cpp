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
ld eps = 1e-14L;
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
                        ld curx = pos[k][0] + dp[i][k] * dir[k][0], cury = pos[k][1] + dp[i][k] * dir[k][1];
                        if(i == 0){
                            curx = 0, cury = 0;
                        }
                        ld posx = pos[j][0] + dp[i][k] * dir[j][0], posy = pos[j][1] + dp[i][k] * dir[j][1];
                        ld difx = posx - curx, dify = posy - cury;
                        ld a = dir[j][0] * dir[j][0] + dir[j][1] * dir[j][1] - c * c;
                        ld b = 2 * (difx * dir[j][0] + dify * dir[j][1]), c1 = difx * difx + dify * dify;
                        ld det = b * b - 4 * a * c1;
                        det = max(ld(0), det);
                        ld t1 = (-b + sqrt(det)) / 2 / a, t2 = (-b - sqrt(det)) / 2 / a;
                        ld t3 = min(t1, t2) < 0 ? max(t1, max(t2, ld(0))) : min(t1, t2);
                        dp[newmask][j] = min(dp[newmask][j], dp[i][k] + t3);
                        
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
