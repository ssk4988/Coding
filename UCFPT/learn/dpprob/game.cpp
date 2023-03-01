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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        ld pa, pb;
        int k, l;
        cin >> pa >> pb >> k >> l;
        pa /= 100, pb /= 100;
        vector<vector<vector<ld>>> game(l + 1, vector<vector<ld>>(l + 1, vector<ld>(2, -1)));
        rep(i, 0, l)
        {
            game[i][l][1] = 0;
            game[l][i][0] = 1;
        }
        auto solve = [&](int numa, int numb, int turn, auto &&solve) -> ld
        {
            if (game[numa][numb][turn] >= 0)
                return game[numa][numb][turn];
            game[numa][numb][turn] = 0;
            game[numa][numb][turn] += (turn == 0 ? pa : 1 - pb) * solve(numa + 1, numb, 0, solve);
            game[numa][numb][turn] += (turn == 0 ? 1 - pa : pb) * solve(numa, numb + 1, 1, solve);
            return game[numa][numb][turn];
        };
        vector<vector<vector<ld>>> m(k + 1, vector<vector<ld>>(k + 1, vector<ld>(2, -1)));
        m[1][0][0] = 0.5 * solve(0, 0, 0, solve) + 0.5 * solve(0, 0, 1, solve);
        m[0][1][1] = 1 - m[1][0][0];
        rep(i, 0, k + 1)
        {
            rep(j, 0, k + 1)
            {
                rep(t, 0, 2)
                {
                    if (m[i][j][t] < 0)
                        continue;
                    if (i == k || j == k)
                        continue;
                    int i1 = i + 1, j1 = j, t1 = 0;
                    m[i1][j1][t1] = max((ld)0, m[i1][j1][t1]);
                    m[i1][j1][t1] += m[i][j][t] * solve(0, 0, t, solve);
                    i1 = i, j1 = j + 1, t1 = 1;
                    m[i1][j1][t1] = max((ld)0, m[i1][j1][t1]);
                    m[i1][j1][t1] += m[i][j][t] * (1 - solve(0, 0, t, solve));
                }
            }
        }
        ld wina = 0;
        rep(i, 0, k)
        {
            wina += m[k][i][0];
        }
        cout << fixed << setprecision(1) << 100 * wina << nL;
    }

    return 0;
}
