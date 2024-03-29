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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    if(n <= 2){
        cout << -1 << nL;
        return 0;
    }
    bool side = n % 2 == 0; // true = on bottom row, false = on right col
    int used = 1;
    vvi grid(n, vi(n));
    rep(x, 0, n - 3){
        if(side){
            for(int i = n - 1; i >= x; i--){
                grid[i][x] = used++;
            }
            for(int j = x + 1; j <= n-1; j++){
                grid[x][j] = used++;
            }
        }
        else{
            for(int j = n - 1; j >= x; j--){
                grid[x][j] = used++;
            }
            for(int i = x + 1; i <= n - 1; i++){
                grid[i][x] = used++;
            }
        }
        side = !side;
    }
    grid[n-3][n-1] = used++;
    grid[n-1][n-2] = used++;
    grid[n-2][n-3] = used++;
    grid[n-2][n-2] = used++;
    grid[n-2][n-1] = used++;
    grid[n-1][n-1] = used++;
    grid[n-3][n-3] = used++;
    grid[n-1][n-3] = used++;
    grid[n-3][n-2] = used++;
    rep(i, 0, n){
        rep(j, 0, n){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    

    return 0;
}
