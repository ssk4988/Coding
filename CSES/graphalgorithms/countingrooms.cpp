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
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            grid[i][j] = str[j] == '.';
        }
    }
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int numcomp = 0;
    vvi component(n, vi(m, -1));
    auto floodfill = [&](int i, int j, auto &&floodfill) -> void{
        component[i][j] = numcomp;
        rep(k, 0, 4){
            int i1 = i + ds[k][0], j1 = j + ds[k][1];
            if(i1 >= 0 && i1 < n && j1 >= 0 && j1 < m && component[i1][j1] == -1 && grid[i1][j1]){
                floodfill(i1, j1, floodfill);
            }
        }
    };
    rep(i, 0, n){
        rep(j, 0, m){
            if(component[i][j] == -1 && grid[i][j]){
                floodfill(i, j, floodfill);
                numcomp++;
            }
        }
    }
    cout << numcomp << nL;
    
    return 0;
}
