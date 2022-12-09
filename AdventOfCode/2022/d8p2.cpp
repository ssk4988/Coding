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
    int n;
    cin >> n;
    vvi grid(n);
    rep(i, 0, n){
        string str;
        cin >> str;
        rep(j, 0, str.length()){
            grid[i].pb(str[j] - '0');
        }
    }
    int m = grid[0].size();
    vector<vector<bool>> vis(grid.size(), vector<bool>(m, false));
    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, 1, 0, -1};
    int ans = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            int sc = 1;
            rep(k, 0, 4){
                int r = i + dr[k];
                int c = j + dc[k];
                int cur = 0;
                while(0 <= r && r < n && 0 <= c && c < m){
                    cur++;
                    if(grid[i][j] <= grid[r][c]){
                        break;
                    }
                    r += dr[k];
                    c += dc[k];
                }
                sc *= cur;
            }
            ans = max(ans, sc);
        }
    }
    cout << ans << nL;

    
    return 0;
}