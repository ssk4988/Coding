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
    int r, c;
    cin >> r >> c;
    r--,c--;
    vvi ds = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    vvi deg(8, vi(8));
    rep(i, 0, 8)
    {
        rep(j, 0, 8)
        {
            rep(k, 0, 8)
            {
                int i1 = i + ds[k][0], j1 = j + ds[k][1];
                if (i1 < 0 || i1 >= 8 || j1 < 0 || j1 >= 8)
                    continue;
                deg[i1][j1]++;
            }
        }
    }
    vvi order(8, vi(8, -1));
    int curi = c, curj = r;
    int movenum = 1;
    while (curi != -1)
    {
        bool foundnext = false;
        order[curi][curj] = movenum++;
        int besti = -1, bestj = -1;
        rep(k, 0, 8)
        {
            int i1 = curi + ds[k][0], j1 = curj + ds[k][1];
            if (i1 < 0 || i1 >= 8 || j1 < 0 || j1 >= 8 || order[i1][j1] != -1)
                continue;
            deg[i1][j1]--;
            if(besti == -1 || deg[i1][j1] <= deg[besti][bestj]) {
                besti = i1, bestj = j1;
            }
        }
        curi = besti, curj = bestj;
    }
    rep(i, 0, 8){
        rep(j, 0, 8){
            cout << order[i][j] << " ";
        }
        cout << nL;
    }

    return 0;
}
