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

using dt = pair<ll, pair<pi, pi>>;

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        int gsize = 33;
        vvl paths(gsize, vl(gsize)), rpaths(gsize, vl(gsize));
        vector<vvi> edge(gsize, vvi(gsize, vi(2))), redge(gsize, vvi(gsize, vi(2)));
        rep(i, 0, gsize){
            rep(j, 0, gsize){
                if(i + 1 < gsize){
                    edge[i][j][0] = 1;
                    redge[i+1][j][0] = 1;
                }
                if(j + 1 < gsize){ 
                    edge[i][j][1] = 1;
                    redge[i][j+1][1] = 1;
                }
            }
        }
        // set grid[0][0] = 1 first
        auto calcforward = [&]() -> void{
            rep(i, 0, gsize){
                rep(j, 0, gsize){
                    paths[i][j] = 0;
                }
            }
            paths[0][0] = 1;
            rep(i, 0, gsize){
                rep(j, 0, gsize){
                    if(edge[i][j][0]){
                        paths[i+1][j] += paths[i][j];
                    }
                    if(edge[i][j][1]) paths[i][j + 1] += paths[i][j];
                }
            }
        };
        
        auto calcreverse = [&]() -> void{
            rep(i, 0, gsize){
                rep(j, 0, gsize){
                    rpaths[i][j] = 0;
                }
            }
            rpaths[gsize - 1][gsize - 1] = 1;
            for(int i = gsize - 1; i >= 0; i--){
                for(int j = gsize - 1; j >= 0; j--){
                    if(redge[i][j][0]){
                        rpaths[i-1][j] += rpaths[i][j];
                    }
                    if(redge[i][j][1]) rpaths[i][j - 1] += rpaths[i][j];
                }
            }
        };

        calcforward();
        calcreverse();
        int iterations = 0;
        while(paths[gsize - 1][gsize - 1] > n){
            // cout << paths[gsize - 1][gsize - 1] << " " << rpaths[0][0] << nL;
            vector<dt> rem;
            ll diff = paths[gsize - 1][gsize - 1] - n;
            rep(i, 0, gsize){
                rep(j, 0, gsize){
                    rep(k, 0, 2){
                        if(!edge[i][j][k]) continue;
                        int i1 = i + (k == 0), j1 = j + (k == 1);
                        ll score = paths[i][j] * rpaths[i1][j1];
                        if(score > 0) {
                            rem.pb({score, {{i, j}, {i1, j1}}});
                        }
                    }
                }
            }
            sort(all(rem));
            dt remo;
            bool foundOne = false;
            for(auto &d : rem){
                if(d.first >= diff / 2){
                // if(true){
                    remo = d;
                    foundOne = true;
                    break;
                }
            }
            if(!foundOne && rem.size() > 0){
                remo = rem.front();
                foundOne = true;
            }
            assert(foundOne);

            // cout << "score to rem: " << remo.f << nL;
            int ij = remo.s.s.f == remo.s.f.f;
            edge[remo.s.f.f][remo.s.f.s][ij] = 0;
            redge[remo.s.s.f][remo.s.s.s][ij] = 0;
            calcforward();
            calcreverse();
            iterations++;
            // cout << iterations << nL;
        }
        assert(rpaths[0][0] == n);
        // cout << paths[gsize - 1][gsize - 1] << nL;
        int boardsize = gsize * 2 - 1;
        vector<vector<char>> ans(boardsize, vector<char>(boardsize, '*'));
        rep(i, 0, gsize){
            rep(j, 0, gsize){
                int i1 = 2 * i, j1 = 2 * j;
                ans[i1][j1] = '.';
                if(edge[i][j][0]){
                    ans[i1 + 1][j1] = '.';
                }
                if(edge[i][j][1]){
                    ans[i1][j1 + 1] = '.';
                }
            }
        }
        cout << boardsize << " " << boardsize << nL;
        rep(i, 0, boardsize){
            rep(j, 0, boardsize){
                cout << ans[i][j];
            }
            cout << nL;
        }
    }
    
    return 0;
}