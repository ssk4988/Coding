#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

// #define bitat(b, x) (b & (1LL << x))
#define bitat(b, x) (((b) >> (x)) & 1)
#define encode(r, c) ((r) * 6 + (c))
#define getr(x) ((x) / 6)
#define getc(x) ((x) % 6)

// set<pair<ll, ll>> conf;
struct Conf {
    ll placed, blocked;
    vi places;
    int cause[6][6];
    int id;
    Conf(ll p, ll b, vi pl, int id = 0) : placed(p), blocked(b), places(pl), id(id){
        memset(cause, -1, sizeof cause);
        rep(i, 0, 6){
            rep(j, 0, 6){
                if(bitat(blocked, encode(i, j))){
                    rep(i1, i - 1, i + 1){
                        rep(j1, j - 1, j + 1){
                            if(i1 >= 0 && j1 >= 0 && bitat(placed, encode(i1, j1))){
                                cause[i][j] = encode(i1, j1);
                            }
                        }
                    }
                    // assert(cause[i][j] != -1);
                }
            }
        }
    }
    void display(){
        vector<string> grid(6);
        map<int, int> rl;
        cout << "Configuration " << id << ": \n";
        rep(i, 0, 6){
            rep(j, 0, 6){
                grid[i].push_back('.');
                if(cause[i][j] != -1){
                    if(!rl.count(cause[i][j])){
                        rl[cause[i][j]] = sz(rl);
                    }
                    grid[i][j] = 'A' + rl[cause[i][j]];
                }
            }
            cout << grid[i] << "\n";
        }
        
    }
};
vector<Conf> confs;
void backtrack(ll placed, ll blocked, vi &places, int row, int col) {
    if(row == 6){
        Conf c(placed, blocked, places, sz(confs));
        confs.emplace_back(c);
        return;
    }
    int ncol = (col + 1) % 6;
    int nrow = row + (ncol == 0);
    backtrack(placed, blocked, places, nrow, ncol); // dont place
    if(col + 1 >= 6 || row + 1 >= 6 
        || bitat(blocked, encode(row, col)) 
        || bitat(blocked, encode(row, col + 1)) 
        || bitat(blocked, encode(row + 1, col))){
        // blocked by previous placements or cant even place
        return;
    }
    ll newblocked = blocked;
    rep(r, row, row + 2){
        rep(c, col, col + 2){
            newblocked ^= 1LL << encode(r, c);
        }
    }
    places.push_back(encode(row, col));
    backtrack(placed ^ (1LL << encode(row, col)), newblocked, places, nrow, ncol);
    places.pop_back();
}



int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi ppppp;
    backtrack(0, 0, ppppp, 0, 0);
    // cout << sz(confs) << "\n";
    int h; cin >> h;
    vector<string> as(h), bs(h);
    rep(i, 0, h){
        cin >> as[i];
    }
    rep(i, 0, h) cin >> bs[i];
    reverse(all(as));
    reverse(all(bs));
    int n = sz(confs); // 6427
    //      |
    //A row |
    //      |_______
    //         B (col)
    // 0 is empty state
    vvi valid(h, vi(n, -1)); // -1 if not valid, otherwise has num free blocks
    // cout << confs[0].placed << " " << confs[0].blocked << " " << confs[0].id << "\n";
    int maxplaced = 0;
    vi relevant(n);
    rep(i, 0, h){
        rep(j, 0, n){
            Conf &c = confs[j];
            maxplaced = max(maxplaced, sz(c.places));
            // x is dim we see, y is depth
            bool isvalid = true;
            map<int, char> col;
            rep(x, 0, 6){
                if(!isvalid) break;
                if(as[i][x] == '.'){
                    bool used = false;
                    rep(y, 0, 6){
                        used = used || bitat(c.blocked, encode(x, y));
                    }
                    if(used) isvalid = false;
                }
                else{
                    bool seen = false;
                    rep(y, 0, 6){
                        if(bitat(c.blocked, encode(x, y))){
                            int p = c.cause[x][y];
                            seen = true;
                            // rep(x1, x - 1, x + 1){
                            //     rep(y1, y - 1, y + 1){
                            //         if(x1 >= 0 && y1 >= 0 && bitat(c.placed, encode(x1, y1))) p = encode(x1, y1);
                            //     }
                            // }
                            // assert(p != -1);
                            if(col.count(p) && col[p] != as[i][x]) isvalid = false;
                            col[p] = as[i][x];
                            break;
                        }
                    }
                    if(!seen) isvalid = false;
                }
                if(bs[i][x] == '.'){
                    bool used = false;
                    for(int y = 5; y >= 0; y--) {
                        used = used || bitat(c.blocked, encode(y, x));
                    }
                    if(used) isvalid = false;
                }
                else{
                    bool seen = false;
                    for(int y = 5; y >= 0; y--){
                        if(bitat(c.blocked, encode(y, x))){
                            int p = c.cause[y][x];
                            seen = true;
                            // rep(x1, x - 1, x + 1){
                            //     rep(y1, y - 1, y + 1){
                            //         if(x1 >= 0 && y1 >= 0 && bitat(c.placed, encode(y1, x1))) p = encode(y1, x1);
                            //     }
                            // }
                            // assert(p != -1);
                            if(col.count(p) && col[p] != bs[i][x]) isvalid = false;
                            col[p] = bs[i][x];
                            break;
                        }
                    }
                    if(!seen) isvalid = false;
                }
            }
            if(isvalid){
                // assert(sz(c.places) >= sz(col));
                int freenum = sz(c.places) - sz(col);
                valid[i][j] = freenum;
                relevant[j]++;
            }
        }
    }
    vvi adj(n);
    ll ops = 0, ops1 = 0;
    rep(i, 0, n){
        if(!relevant[i]) continue;
        rep(j, 0, n){
            if(!relevant[j]) continue;
            Conf &c1 = confs[i], &c2 = confs[j];
            bool isvalid = true;
            for(int x : c2.places){
                int k = getr(x), l = getc(x);
                // assert(bitat(c2.placed, encode(k, l)));
                bool covered = false;
                // ops1++;
                rep(k1, k, k + 2){
                    rep(l1, l, l + 2){
                        // ops++;
                        if(k1 < 6 && l1 < 6 && bitat(c1.blocked, encode(k1, l1))){
                            covered = true;
                            break;
                        }
                    }
                }
                if(!covered){
                    isvalid = false;
                    break;
                }

            }
            // rep(k, 0, 6){
            //     rep(l, 0, 6){
            //         if(bitat(c2.placed, encode(k, l))){
            //         }
            //     }
            // }
            if(isvalid){
                adj[i].push_back(j);
            }
        }
    }
    vector<vl> dp(h, vl(n));
    // cout << maxplaced <<"\n";
    vector<ll> pows(maxplaced + 3);
    pows[0] = 1;
    rep(i, 1, sz(pows)){
        pows[i] = pows[i - 1] * 3;
    }
    rep(i, 0, n){
        if(valid[0][i] != -1){
            dp[0][i] = pows[valid[0][i]];
        }
    }
    rep(i, 0, h - 1){
        rep(j, 0, n){
            for(int k : adj[j]){
                if(valid[i + 1][k] == -1 || dp[i][j] == 0) continue;
                dp[i + 1][k] += dp[i][j] * pows[valid[i + 1][k]];
                // if(d)
                // cout << "transition from " << j << " to " << k << " with cont " << dp[i][j] * pows[valid[i + 1][k]] << "\n"; 
                // confs[j].display();
                // confs[k].display();
            }
        }
    }
    // rep(i, 0, h){
    //     rep(j, 0, n){
    //         if(valid[i][j]){
    //             cout << "configuration " << j << " works on height " << i << " with info " << confs[j].placed << " " << confs[j].blocked << "\n";
    //         }
    //     }
    // }
    ll ans = 0;
    rep(i, 0, n){
        ans += dp[h - 1][i];
    }
    cout << ans << "\n";
    // cout << "ops: " << ops << " " << ops1 << "\n";
    return 0;
}
