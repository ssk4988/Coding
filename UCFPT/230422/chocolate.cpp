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
        auto solve2 = [&](int row, int col, vector<vvi> &bd, vvi &used, auto &&solve2)->bool{
            if(row == 3 && col == 0) return true;
            int nextrow = col == 2 ? row + 1 : row;
            int nextcol = col == 2 ? 0 : col + 1;
            if(bd[row][col][0] != -1 && bd[row][col][1] != -1){
                if(solve2(nextrow, nextcol, bd, used, solve2)){
                    return true;
                }
            }
            rep(i, 0, 3){
                if(bd[row][col][0] != -1 && bd[row][col][0] != i) continue;
                rep(j, 0, 3){
                    if(bd[row][col][1] != -1 && bd[row][col][1] != j) continue;
                    if(used[i][j]) continue;
                    used[i][j] = 1;
                    if(solve2(nextrow, nextcol, bd, used, solve2)){
                        bd[row][col][0] = i;
                        bd[row][col][1] = j;
                        return true;
                    }
                    used[i][j] = 0;
                }
            }
            return false;
        };
        auto solve = [&](int cluenum, vector<vector<vector<int>>> &bd, vvi &used, auto && solve)->bool{
            if(cluenum == n){
                return solve2(0, 0, bd, used, solve2);
            };
            rep(i, 0, 3 - siz[cluenum].f + 1){
                rep(j, 0, 3 - siz[cluenum].s + 1){
                    bool bad = false;
                    vector<vvi> newbd(bd);
                    vvi newused(used);
                    rep(k, 0, sz(clues[cluenum])){
                        if(newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] != -1){
                            if(newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] != clues[cluenum][k][3]){
                                bad = true;
                                break;
                            }
                            else{
                                continue;
                            }
                        }
                        newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][clues[cluenum][k][2]] = clues[cluenum][k][3];
                        if(newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0] != -1 && newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1] != -1){
                            if(newused[newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0]][newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1]]){
                                bad = true;
                                break;
                            }
                            newused[newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][0]][newbd[i + clues[cluenum][k][0]][j + clues[cluenum][k][1]][1]] = 1;
                        }
                    }
                    if(!bad && solve(cluenum + 1, newbd, newused, solve)){
                        bd = newbd;
                        used = newused;
                        return true;
                    }
                }
            }
            return false;
        };
        vector<vector<vector<int>>> bd(3, vvi(3, vi(2, -1)));
        vvi used(3, vi(3));
        bool works = solve(0, bd, used, solve);
        assert(works);
        cout << "Puzzle #" << (cn + 1) << ":\n";
        rep(i, 0, 3){
            rep(j, 0, 3){
                rep(k, 0, 2){
                    assert(bd[i][j][k] != -1);
                    cout << (k == 0 ? shape : flavor)[bd[i][j][k]];
                }
                if(j + 1 < 3) cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}