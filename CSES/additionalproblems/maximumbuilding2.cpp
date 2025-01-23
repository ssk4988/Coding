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

// 1 if blocked
vvi count_rectangles(vvi grid) {
    int n = sz(grid), m = sz(grid[0]);
    vi colspace(m);
    rep(r, 0, n) {
        rep(c, 0, m){
            if(grid[r][c]) colspace[r][c] = 0;
            else colspace[r][c]++;
        }
        vi l(m, -1), r(m, m);
        rep(c, 0, m) {
            int i = c-1;
            for(; i >= 0 && colspace[i] >= colspace[c];) {
                r[i] = c;
                i = l[i];
            }
            l[c] = i;
        }
        
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vvi grid(n, vi(m, 1));
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        rep(j, 0, sz(str))
        {
            if (str[j] == '.')
                grid[i][j] = 0;
        }
    }
    

}
