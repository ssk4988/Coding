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
vvi count_rectangles(vvi &grid) {
    int n = sz(grid), m = sz(grid[0]);
    vvi ans(n+1, vi(m+1));
    vi col(m); // free space in column
    rep(r, 0, n) {
        rep(c, 0, m)
            if(grid[r][c]) col[c] = 0;
            else col[c]++;
        vi pre(m, -1), nex(m, m);
        rep(c, 0, m) {
            int i = c-1;
            while(i >= 0 && col[i] >= col[c]) {
                nex[i] = c;
                i = pre[i];
            }
            pre[c] = i;
        }
        rep(c, 0, m) {
            int left = c - pre[c] - 1, right = nex[c] - c - 1;
            ans[col[c]][left + right + 1]++;
            ans[col[c]][left]--;
            ans[col[c]][right]--;
        }
    }
    rep(i, 1, n+1)
        rep(t, 0, 2)
            for(int j = m-1; j; j--) ans[i][j] += ans[i][j+1];
    rep(j, 1, m+1)
        for(int i = n-1; i; i--) ans[i][j] += ans[i+1][j];
    return ans;
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
    
    vvi res = count_rectangles(grid);
    rep(i, 1, n+1) {
        rep(j, 1, m+1) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
}
