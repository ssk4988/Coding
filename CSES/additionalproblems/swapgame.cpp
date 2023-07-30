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

int hsh(vvi &g)
{
    int h = 0;
    int mult = 1;
    rep(i, 0, 3)
    {
        rep(j, 0, 3)
        {
            h += mult * g[i][j];
            mult *= 9;
        }
    }
    return h;
};
int pows[15];
int swp(int h, int idx1, int idx2){
    int v1 = (h % pows[idx1 + 1]) / pows[idx1];
    int v2 = (h % pows[idx2 + 1]) / pows[idx2];
    return h - pows[idx1] * v1 - pows[idx2] * v2 + pows[idx1] * v2 + pows[idx2] * v1;
}
vvi unhash(int h)
{
    vvi res(3, vi(3));
    rep(i, 0, 3)
    {
        rep(j, 0, 3)
        {
            int v = h % 9;
            res[i][j] = v;
            h /= 9;
        }
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    pows[0] = 1;
    rep(i, 1, 15) pows[i] = 9 * pows[i - 1];
    vvi grid(3, vi(3));
    rep(i, 0, 3)
    {
        rep(j, 0, 3)
        {
            cin >> grid[i][j];
            grid[i][j]--;
        }
    }
    vvi target(3, vi(3));
    rep(i, 0, 3)
    {
        rep(j, 0, 3)
        {
            target[i][j] = i * 3 + j;
        }
    }
    int targethash = hsh(target);

    vector<bool> seen(pows[9]);
    queue<pi> q;
    q.push({hsh(grid), 0});
    seen[hsh(grid)] = true;
    int ans = 0;
    while (!q.empty())
    {
        auto [h, v] = q.front();
        q.pop();
        if(h == targethash){
            ans = v;
            break;
        }
        // vvi g = unhash(h);
        rep(i, 0, 3)
        {
            rep(j, 0, 2)
            {
                // swap(g[i][j], g[i][j + 1]);
                // int h1 = hsh(g);
                int h1 = swp(h, i * 3 + j, i * 3 + j + 1);
                if (seen[h1] == 0){
                    q.push({h1, 1 + v});
                    seen[h1] = true;
                }
                // swap(g[i][j], g[i][j + 1]);
            }
        }
        rep(i, 0, 2)
        {
            rep(j, 0, 3)
            {
                // swap(g[i][j], g[i + 1][j]);
                // int h1 = hsh(g);
                int h1 = swp(h, i * 3 + j, (i + 1) * 3 + j);
                if (seen[h1] == 0){
                    q.push({h1, 1 + v});
                    seen[h1] = true;
                }
                // swap(g[i][j], g[i + 1][j]);
            }
        }
    }

    cout << ans << nL;

    return 0;
}