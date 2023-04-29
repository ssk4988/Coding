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

// void solve(int cur, int used){
//     if(cur == 37){
//         ans = min(ans, used);
//     }
//     int run = 0;
//     for(int i = cur + 2; i <= 37; i += 2){
//         run += pfs[i - 1];
//     }
// }
pi pts[200];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    while(true){
        int n;
        int ans = 300;
        cin >> n;
        if(n == 0) break;
        // vvi pts = vvi(n, vi(2));
        // pfs = vi(37);
        rep(i, 0, n){
            cin >> pts[i].f >> pts[i].s;
        }
        sort(pts, pts + n);
        vector<vector<vi>> stuff(n, vvi(n + 1));
        for(int i = 0; i < n; i++){
            for(int j = i; j <= n; j++){
                for(int k = i; k < j; k++){
                    stuff[i][j].pb(pts[k].s);
                }
                sort(all(stuff[i][j]));
            }
        }
        vi freq(37);
        rep(i, 0, n){
            freq[pts[i].f]++;
        }
        vi x;
        rep(i, 0, 37){
            if(freq[i]){
                x.pb(i + 1);
            }
        }
        // ptsy = vvi(pts);
        // // by reference sus
        // sort(all(ptsy), [](vi &a, vi &b)->bool{
        //     if(a[1] != b[1]) return a[1] < b[1];
        //     if(a[0] != b[0]) return a[0] < b[0];
        //     return a[2] < b[2];
        // });
        // rep(i, 1, 37){
        //     pfs[i] += pfs[i - 1];
        // }

        // vi lbl(n);

        int upb = 1 << sz(x);
        int x1 = sz(x);
        rep(i, 0, upb){
            int pnter = 0;
            int used = 0;
            vpi ivs;
            rep(j, 0, x1){
                if(i & (1 << j)){
                    used++;
                    int j1 = x[j];
                    if(pnter < n){
                        int prevpt = pnter;
                        while(pnter < n && pts[pnter].f < j1){
                            // cps.back().pb(pts[pnter][1]);
                            pnter++;
                        }
                        for(int k = 0; k + 1 < sz(stuff[prevpt][pnter]); k++){
                            // cout << "k";
                            ivs.emplace_back(stuff[prevpt][pnter][k + 1] - 1, stuff[prevpt][pnter][k]);
                        }

                    }
                    // cps.pb({});
                }
            }
            if(used >= ans) continue;
            // cout << "last mask: " << i << nL;
            // if(i == 191){
            //     cout << "bruh";
            // }
            if(pnter < n){
                int prevpt = pnter;
                while(pnter < n){
                    // cps.back().pb(pts[pnter][1]);
                    pnter++;
                }
                for(int k = 0; k + 1 < sz(stuff[prevpt][pnter]); k++){
                    ivs.emplace_back(stuff[prevpt][pnter][k + 1] - 1, stuff[prevpt][pnter][k]);
                }
            }
            // rep(i1, 0, cp){
            //     sort(all(cps[i1]));
            //     rep(j, 0, sz(cps[i1]) - 1){
            //         ivs.emplace_back(cps[i1][j + 1] - 1, cps[i1][j]);
            //     }
            // }
            sort(all(ivs));
            int pre = -5;
            for(auto &p : ivs){
                if(p.s < pre) continue;
                used++;
                pre = p.f;
            }
            // if(used < ans){
            //     cout << i << " " << used << " " << ans << nL;
            // }
            ans = min(ans, used);
        }
        cout << ans << nL;
    }
    




    return 0;
}