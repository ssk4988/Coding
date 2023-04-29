#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        vvi grid(n, vi(m));
        rep(i, 0, n){
            rep(j, 0, m){
                cin >> grid[i][j];
                if(i > 0) grid[i][j] += grid[i - 1][j];
                if(j > 0) grid[i][j] += grid[i][j - 1];
                if(i > 0 && j > 0) grid[i][j] -= grid[i - 1][j- 1];
            }
        }
        int best = 0;
        rep(i, 0, n){
            rep(j, 0, m){
                int lo = -1, hi = min(n - i - 1, m - j - 1);
                while(lo < hi){
                    int mid = lo + (hi - lo + 1) / 2;
                    int sq = grid[i + mid][j + mid];
                    if(i > 0){
                        sq -= grid[i - 1][j + mid];
                    }
                    if(j > 0) sq -= grid[i + mid][j - 1];
                    if(i > 0 && j > 0) sq += grid[i - 1][j - 1];
                    if(sq == (mid + 1) * (mid + 1)){
                        lo = mid;
                    }
                    else{
                        hi = mid - 1;
                    }
                }
                best = max(best, lo + 1);
            }
        }
        cout << best << "\n";
    }

    return 0;
}