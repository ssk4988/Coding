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

vector<array<int, 2>> ds = {{1, 0}, {1, -1}, {1, 1}, {0, 1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
vvi o, c, b, m;
bool solve(int row, int col, int cnt)
{
    if (row == 7 || cnt > 10)
    {
        bool solved = cnt == 10 && row == 7;
        rep(i, 0, 7)
        {
            rep(j, 0, 7)
            {
                if (c[i][j])
                    solved = false;
            }
        }
        return solved;
    }
    int ncol = (col + 1) % 7, nrow = row + (col == 6);
    // don't put anything
    bool c1 = ((row == 0 || col == 0) || c[row - 1][col - 1] == 0) && solve(nrow, ncol, cnt);
    if (c1)
    {
        return true;
    }
    // if this has a number, can't put anything
    if (m[row][col])
        return c1;
    for (auto [dr, dc] : ds)
    {
        int r1 = row + dr, c1 = col + dc;
        if (r1 < 0 || c1 < 0 || r1 >= 7 || c1 >= 7 || !m[r1][c1])
            continue;
        if (c[r1][c1] < 1)
            return false;
    }
    for (auto [dr, dc] : ds)
    {
        int r1 = row + dr, c1 = col + dc;
        if (r1 < 0 || c1 < 0 || r1 >= 7 || c1 >= 7 || !m[r1][c1])
            continue;
        c[r1][c1]--;
    }
    b[row][col] = true;
    bool c2 = ((row == 0 || col == 0) || c[row - 1][col - 1] == 0) && solve(nrow, ncol, cnt + 1);
    if (c2)
        return true;
    b[row][col] = false;
    for (auto [dr, dc] : ds)
    {
        int r1 = row + dr, c1 = col + dc;
        if (r1 < 0 || c1 < 0 || r1 >= 7 || c1 >= 7 || !m[r1][c1])
            continue;
        c[r1][c1]++;
    }
    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        o = vvi(7, vi(7));
        m = vvi(7, vi(7));
        rep(i, 0, 7)
        {
            string str;
            cin >> str;
            rep(j, 0, 7)
            {
                if (str[j] != '.')
                {
                    o[i][j] = str[j] - '0';
                    m[i][j] = true;
                }
            }
        }
        c = vvi(o);
        b = vvi(7, vi(7));
        bool c1 = solve(0, 0, 0);
        assert(c1);
        cout << "Tentaizu Board #" << (cn + 1) << ":\n";
        bool works = true;
        c = vvi(o);
        rep(i, 0, 7)
        {
            rep(j, 0, 7)
            {
                if (m[i][j])
                    cout << o[i][j];
                else if (b[i][j])
                {
                    cout << "*";
                    for (auto [dr, dc] : ds)
                    {
                        int r1 = i + dr, c1 = j + dc;
                        if (r1 < 0 || c1 < 0 || r1 >= 7 || c1 >= 7 || !m[r1][c1])
                            continue;
                        c[r1][c1]--;
                    }
                }
                else
                    cout << ".";
            }
            cout << nL;
        }
        cout << nL;
        rep(i, 0, 7){
            rep(j, 0, 7){
                if(c[i][j]) works = false;
            }
        }
        assert(works);
        // if(c1){
        //     cout << "bruh";
        // }
    }

    return 0;
}
