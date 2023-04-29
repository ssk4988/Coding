#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    string flavor = "VSC";
    string shape = "SRT";
    rep(cn, 0, nc){
        int n; cin >> n;
        vpi siz(n);
        vector<vector<vi>> clues(n);
        rep(i, 0, n){
            cin >> siz[i].f >> siz[i].s;
            rep(j, 0, siz[i].f){
                rep(k, 0, siz[i].s){
                    string str; cin >> str;
                    rep(l, 0, 2){
                        if(str[l] == '_') continue;
                        vi ins = {j, k, l};
                        string &st = l == 0 ? shape : flavor;
                        rep(v, 0, 3){
                            if(str[l] == st[v]){
                                ins.pb(v);
                                break;
                            }
                        }
                        clues[i].pb(ins);
                    }
                }
            }
        }
        vector<vector<vector<int>>> bd(3, vvi(3, vi(2, -1)));
        vvi used(3, vi(3));
        auto solve2 = [&](int row, int col, auto &&solve2)->bool{
            if(row == 3 && col == 0) return true;
            int nextrow = col == 2 ? row + 1 : row;
            int nextcol = col == 2 ? 0 : col + 1;
            if(bd[row][col][0] != -1 && bd[row][col][1] != -1){
                if(solve2(nextrow, nextcol, solve2)){
                    return true;
                }
            }
            rep(i, 0, 3){
                if(bd[row][col][0] != -1 && bd[row][col][0] != i) continue;
                rep(j, 0, 3){
                    if(bd[row][col][1] != -1 && bd[row][col][1] != j) continue;
                    if(used[i][j]) continue;
                    used[i][j] = 1;
                    vi prevstate = {bd[row][col][0], bd[row][col][1]};
                    bd[row][col][0] = i;
                    bd[row][col][1] = j;
                    if(solve2(nextrow, nextcol, solve2)) return true;
                    bd[row][col] = prevstate;
                    used[i][j] = 0;
                }
            }
            return false;
        };
        auto solve = [&](int cluenum, auto && solve)->bool{
            if(cluenum == n){
                return solve2(0, 0, solve2);
            };
            vvi prevstate;
            vvi prevunused;
            rep(i, 0, 3 - siz[cluenum].f + 1){
                rep(j, 0, 3 - siz[cluenum].s + 1){
                    prevstate.clear();
                    // bool works = true;
                    // rep(k, 0, sz(clues[cluenum])){
                    //     if(!(bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] == -1 || bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] == clues[cluenum][k][3])){
                    //         works = false;
                    //         break;
                    //     }
                    //     if(bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1 - clues[cluenum][k][2]] != -1){
                    //         inp[1 - clues[cluenum][k][2]] = bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1 - clues[cluenum][k][2]];
                    //         inp[clues[cluenum][k][2]] = clues[cluenum][k][3];
                    //         if(inp[0] != -1 && inp[1] != -1 && used[inp[0]][inp[1]]){
                    //             works = false;
                    //             break;
                    //         }
                    //     }
                    // }
                    // if(!works) continue;
                    rep(k, 0, sz(clues[cluenum])){
                        clearing[k] = bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] == -1;
                        bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] = clues[cluenum][k][3];
                        if(bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0] != -1 && bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1] != -1 && clearing[k]){
                            unuse[k] = true;
                            used[bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0]][bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1]] = 1;
                        }
                        else{
                            unuse[k] = false;
                        }
                    }
                    if(solve(cluenum + 1, solve)) return true;
                    for(int k = sz(clues[cluenum]) - 1; k >= 0; k--){
                        if(unuse[k]) used[bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0]][bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1]] = 0;
                        if(clearing[k]) bd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] = -1;
                    }
                }
            }
            return false;
        };
        solve(0, solve);
        cout << "Puzzle #" << (cn + 1) << ":\n";
        rep(i, 0, 3){
            rep(j, 0, 3){
                rep(k, 0, 2){
                    if(bd[i][j][k] == -1) cout << '_';
                    else cout << (k == 0 ? shape : flavor)[bd[i][j][k]];
                }
                if(j + 1 < 3) cout << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}