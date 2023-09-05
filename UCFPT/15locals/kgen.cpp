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
    int n = 64;
    vvi ncr(n, vi(n));
    ncr[0][0] = 1;
    // cout << "row 0: 1\n";
    rep(i, 1, n){
        // cout << "row " << i << ": ";
        rep(j, 0, i + 1){
            if(j) ncr[i][j] += ncr[i-1][j-1];
            if(j < i) ncr[i][j] += ncr[i - 1][j];
            // ncr[i][j] %= 4;
            // cout << ncr[i][j] << " ";
        }
        // cout << "\n";
    }
    vi c(n), b(n, -1);
    rep(i, 0, n){
        rep(j, 0, n - i) cout << " ";
        rep(j, 0, i + 1){
            int p = 0,v;
            for(p = 0, v = ncr[i][j]; v % 2 == 0 && v; v /= 2, p++){
                
            }
            cout << min(p, 2) << " ";
            if(p == 0){
                c[i] += j + 1;
            }
            if(p == 1){
                b[i] = max(b[i], j + 1);
            }
        }
        cout << "\n";
    }
    rep(i, 0, n){
        cout << i << " " << c[i] << " " << (i - b[i] + 1) << "\n";
    }
}
