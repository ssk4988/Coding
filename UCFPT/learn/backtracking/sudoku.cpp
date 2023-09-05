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

vvi g;
vector<vi> rows, cols, sqs;
bool solve(int row, int col){
    if(row == 9){
        return true;
    }    
    int nrow = row + (col == 8), ncol = (col + 1) % 9;
    if(g[row][col]){
        return solve(nrow, ncol);
    }
    rep(i, 1, 10){
        if(rows[row][i] == 0 && cols[col][i] == 0 && sqs[(row / 3) * 3 + col / 3][i] == 0){
            rows[row][i] = true;
            cols[col][i] = true;
            sqs[(row / 3) * 3 + col / 3][i] = true;
            g[row][col] = i;
            bool c = solve(nrow, ncol);
            if(c) return true;
            g[row][col] = 0;
            rows[row][i] = false;
            cols[col][i] = false;
            sqs[(row / 3) * 3 + col / 3][i] = false;
        }
    }
    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        rows = vvi(9, vi(10));  
        cols = vvi(9, vi(10));
        sqs = vvi(9, vi(10));
        g = vvi(9, vi(9));
        bool valid = true;
        rep(i, 0, 9){
            rep(j, 0, 9){
                cin >> g[i][j];
                if(g[i][j]){
                    if(rows[i][g[i][j]] || cols[j][g[i][j]] || sqs[3 * (i / 3) + j / 3][g[i][j]]) valid = false;
                    rows[i][g[i][j]] = true;
                    cols[j][g[i][j]] = true;
                    sqs[3 * (i / 3) + j / 3][g[i][j]] = true;
                }
            }
        }
        // rep(i, 0, 9){
        //     cout << "row " << i << ": ";
        //     for(int j : rows[i]) cout << j << " ";
        //     cout << nL;
        //     cout << "col " << i << ": ";
        //     for(int j : cols[i]) cout << j << " ";
        //     cout << nL;
        // }
        // bool c = false;
        bool c = valid && solve(0, 0);
        cout << "Test case " << (cn + 1) << ":\n";
        if(c){
            rep(i, 0, 9){
                rep(j, 0, 9){
                    cout << g[i][j];
                    if(j + 1 < 9) cout << " ";
                }
                cout << nL;
            }
        }
        else{
            cout << "No solution possible.\n";
        }
        cout << nL;
    }
    
    return 0;
}
