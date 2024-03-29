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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<vpi> point(2, vpi(n));
        vector<string> grid(2);
        rep(i, 0, 2){
            cin >> grid[i];
            rep(j, 0, n){
                if(grid[i][j] == '>'){
                    point[i][j] = {i, j+1};
                }
                else{
                    point[i][j] = {i, j-1};
                }
            }
        }
        vpi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        queue<pi> q;
        vvi inq(2, vi(n));
        inq[0][0] = true;
        q.push({0, 0});
        while(!q.empty()){
            auto [i, j] = q.front(); q.pop();
            for(auto [dr, dc] : ds){
                int i1 = i + dr, j1 = j + dc;
                if(i1 < 0 || j1 < 0 || i1 >= 2 || j1 >= n) continue;
                tie(i1, j1) = point[i1][j1];
                if(!inq[i1][j1]){
                    inq[i1][j1] = true;
                    q.push({i1, j1});
                }
            }
        }
        cout << (inq[1][n-1] ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
