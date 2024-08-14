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
using vvl = vector<vl>;

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
    int l, w, cx, cy, tx, ty, n;
    cout << fixed << setprecision(3) 
    while(true){
        cin >> l >> w >> cx >> cy >> tx >> ty >> n;
        if(l == 0 && w == 0 && cx == 0 && cy == 0 && tx == 0 && ty == 0 && n == 0) break;
        swap(l, w);
        int padleft = tx, padright = w - tx, padtop = l - ty, padbottom = ty;
        int startx = -60 * 2 * w + tx, starty = -60 * 2 * l + ty;
        // ld best = 1e15;
        vvl candidates;
        for(int i = 0; i <= 240; i++){
            int dx = startx + (i % 2 == 0 ? w * i : 2 * w * (i / 2) + 2 * padright);
            for(int j = 0; j <= 240; j++){
                int dy = starty + (j % 2 == 0 ? l * j : 2 * l * (j / 2) + 2 * padtop);
                int obstrwalls = abs(i - 120) + abs(j - 120);
                candidates.pb({dx, dy, obstrwalls});
                // if(obstrwalls == n){

                //     ld newbest = sqrtl((cx - dx) * (cx - dx) + (cy - dy) * (cy - dy));
                //     if(newbest < best){
                //         // cout << dx << " " << dy << nL;
                //     }
                //     best = min(best, newbest);

                // }
            }
        }
        auto dist = [](const vl& p1)->ll{
            return p1[0] * p1[0] + p1[1] * p1[1];
        };
        vl cue = {cx, cy};
        rep(i, 0, sz(candidates)){
            candidates[i][0] -= cue[0];
            candidates[i][1] -= cue[1];
        }
        sort(candidates.begin(), candidates.end(), [&](const vl& p1, const vl& p2)->bool{
            int s1 = p1[1] < 0 || (p1[1] == 0 && p1[0] < 0); 
            int s2 = p2[1] < 0 || (p2[1] == 0 && p2[0] < 0);
            if(s1 != s2) return s1 < s2;
            ll cross = p1[0] * p2[1] - p2[0] * p1[1];
            if(cross != 0) return cross > 0;
            return dist(p1) < dist(p2);
        });
        ld best = 1e15;
        rep(i, 0, sz(candidates)){
            if(i > 0){
                ll cross = candidates[i-1][0] * candidates[i][1] - candidates[i][0] * candidates[i-1][1];
                if(cross == 0) continue;
            }
            if(candidates[i][2] == n) best = min(best, sqrtl(dist(candidates[i])));
        }
        cout << best << nL;
    }
    
    return 0;
}
