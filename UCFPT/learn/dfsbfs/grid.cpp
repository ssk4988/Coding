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
            grid[i][j] = str[j] - '0';
        }
    }
    vvi moves(n, vi(m, -1));
    moves[0][0] = 0;
    queue<pi> q;
    q.push({0, 0});
    vi dr = {1, 0, -1, 0}, dc = {0, 1, 0, -1};
    while(!q.empty()){
        auto [r, c] = q.front(); q.pop();
        rep(i, 0, 4){
            int r1 = r + grid[r][c] * dr[i], c1 = c + grid[r][c] * dc[i];
            if(r1 < 0 || c1 < 0 || r1 >= n || c1 >= m) continue;
            if(moves[r1][c1] == -1){
                q.push({r1, c1});
                moves[r1][c1] = moves[r][c] + 1;
            }
        }
    }
    cout << moves[n-1][m-1] << "\n";
    
    return 0;
}
