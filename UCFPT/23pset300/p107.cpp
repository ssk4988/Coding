#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using ll = long long;
using vpi = vector<pair<int, int>>;
using vl = vector<ll>;
using ld = long double;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
#define nL "\n"


#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    while(true){
        int n;
        int ans = 300;
        cin >> n;
        if(n == 0) break;
        vvi pts(n, vi(3));
        rep(i, 0, n){
            cin >> pts[i][0] >> pts[i][1];
            pts[i][2] = i;
        }
        sort(all(pts));
        vvi ptsy(pts);
        // // by reference sus
        sort(all(ptsy), [](vi &a, vi &b)->bool{
            if(a[1] != b[1]) return a[1] < b[1];
            if(a[0] != b[0]) return a[0] < b[0];
            return a[2] < b[2];
        });

        int upb = 1 << 18;
        rep(i, 0, upb){
            int pnter = 0;
            int used = 0;
            vpi ivs;
            vi comp(n, -1);
            int c = 0;
            rep(j, 0, 18){
                if(i & (1 << j)){
                    used++;
                    int j1 = 1 + 2 * j;
                    if(pnter < n){
                        while(pnter < n && pts[pnter][0] < j1){
                            comp[pts[pnter][2]] = c;
                            pnter++;
                        }
                        c++;
                    }
                }
            }
            if(used >= ans) continue;
            if(pnter < n){
                while(pnter < n){
                    comp[pts[pnter][2]] = c;
                    pnter++;
                }
                c++;
            }

            vi previous(c, -2);
            bool bad = false;
            int last = -1;
            rep(i, 0, n){
                int idx = ptsy[i][2];
                int cc = comp[idx];
                int y = ptsy[i][1];
                if(previous[cc] == y){
                    bad = true;
                    break;
                }
                else{
                    if(last < previous[cc]){
                        if(previous[cc] != -2) used++;
                        last = y - 1;
                    }
                    previous[cc] = y;
                }
            }
            
            if(!bad) ans = min(ans, used);
        }
        cout << ans << nL;
    }

    return 0;
}
