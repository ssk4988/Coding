#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vvi = vector<vi>;
#define pb push_back

const bool DEBUG = false;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        auto printout = [&](int ans)->void{
            cout << "Image #" << (cn + 1) << ": ";
            if(ans == -1) cout << "impossible";
            else cout << ans;
            cout << "\n\n";
        };
        int r, c; cin >> r >> c;
        vvi grid(r, vi(c));
        bool hasone = false;
        rep(i, 0, r){
            string str; cin >> str;
            rep(j, 0, c){
                grid[i][j] = str[j] == '#';
                if(grid[i][j]){
                    hasone = true;
                }
            }
        }
        if(r < 3 || c < 3){
            printout(-1 + (!hasone));
            continue;
        }
        vvi canplace(r, vi(c));
        rep(i,1,r-1){
            rep(j,1,c-1){
                if(grid[i][j] && grid[i - 1][j] && grid[i + 1][j] && grid[i][j - 1] && grid[i][j + 1]) canplace[i][j] = true;
            }
        }
        const int BAD = INT_MAX;
        int b = 1 << (2 * r);
        vvi dp(c - 1, vi(b, BAD));
        vi colbits(c);
        rep(i, 0, c){
            rep(j, 0, r){
                if(!grid[j][i]) colbits[i] ^= 1 << j;
            }
        }
        int initbit = colbits[0] | (colbits[1] << r);
        dp[0][initbit] = 0;
        vi placebit(r);
        vi placebit1(r), placebit2(r);
        rep(i, 1, r - 1){
            placebit[i] ^= 1 << i;
            placebit[i] ^= 1 << (r + i - 1);
            placebit[i] ^= 1 << (r + i);
            placebit[i] ^= 1 << (r + i + 1);
            placebit1[i] ^= 1 << i;
            placebit2[i] ^= 1 << (i - 1);
            placebit2[i] ^= 1 << (i);
            placebit2[i] ^= 1 << (i + 1);
        }
        rep(col, 0, sz(dp) - 1){
            rep(bit, 0, b){
                if(dp[col][bit] == BAD || ((bit & (1 << (0))) == 0) || ((bit & (1 << (r - 1)))) == 0) continue;
                if(DEBUG) cout << "state " << col << " " << bit << " is valid\n";
                vi mandatory, optional;
                int mbit = bit & ((1 << r) - 1), mbit2 = bit >> r, mbit3 = colbits[col + 2];
                bool places = true;
                rep(i, 0, r){
                    if((bit & (1 << (i))) == 0){
                        mandatory.pb(i);
                        if(!canplace[i][col + 1]) places = false;
                        mbit |= placebit1[i];
                        mbit2 |= placebit2[i];
                        mbit3 |= placebit1[i];
                    }
                    else if(canplace[i][col + 1]) optional.pb(i);
                }
                if(!places) continue;
                if(DEBUG) cout << "valid2" << " " << mbit << " " << sz(optional) << "\n";
                rep(i, 0, 1 << sz(optional)){
                    int colbit = mbit, colbit2 = mbit2, colbit3 = mbit3;
                    rep(j, 0, sz(optional)){
                        if(i & (1 << j)){
                            colbit |= placebit1[optional[j]];
                            colbit2 |= placebit2[optional[j]];
                            colbit3 |= placebit1[optional[j]];
                        }
                    }
                    // cout << i << " " << (colbit | bit) << " " << ((1 << r) - 1) << "\n";
                    if(colbit != ((1 << r) - 1)){
                        continue;
                    }
                    int newbit = colbit2 | (colbit3 << r);
                    dp[col + 1][newbit] = min(dp[col + 1][newbit], dp[col][bit] + __builtin_popcount(i) + sz(mandatory));
                    if(DEBUG) {
                        cout << "transition from " << bit << " to " << newbit << " at col " << (col + 1) << " using rows ";
                        for(int j : mandatory){
                            cout << j << " ";
                        }
                        rep(j, 0, sz(optional)){
                            if(i & (1 << j)){
                                cout << optional[j] << " ";
                            }
                        }
                        cout << "\n";
                    }
                }
            }
        }
        if(DEBUG){
            rep(bit, 0, b){
                if(dp.back()[bit] != BAD){
                    cout << "try " << bit << " " << dp.back()[bit] << "\n";
                }
            }
        }
        printout(dp.back().back() == BAD ? -1 : dp.back().back());
    }
}
