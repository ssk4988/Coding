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


#define int long long
const int maxg = 55;

int n, ng;
const int maxn = 15;
// vvi g;
int g[maxn][maxn];
vector<vpi> groups;
ll gv[maxg]; // group value
int go[maxg]; // group operator
// vvi rows, cols;
int rows[maxn][maxn], cols[maxn][maxn];
const bool DEBUG = false;
int mxr = -1;
void display()
{
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            cout << g[i][j];
        }
        cout << nL;
    }
}
bool solve(int gn, int idx)
{
    if (DEBUG && gn > mxr)
    {
        mxr = gn;
        if (DEBUG)
        {
            cout << "reached " << mxr << nL;
            // display();
        }
    }
    if (DEBUG)
    {
        cout << "at " << gn << " " << idx << nL;
    }
    if (gn == ng)
    {
        return true;
    }
    auto [r, c] = groups[gn][idx];
    int ngn = gn + (idx >= sz(groups[gn]) - 1), nidx = (idx >= sz(groups[gn]) - 1) ? 0 : (idx + 1);
    if(idx >= sz(groups[gn]) || go[gn] == 0){
        return solve(gn + 1, 0);
    }
    else if (go[gn] == 1) // +
    {
        rep(i, 1, n + 1)
        {
            if (rows[r][i] || cols[c][i] || gv[gn] < i) //|| gv[gn] - i - (sz(groups[gn]) - 1 - idx) < 0)
                continue;
            gv[gn] -= i;
            rows[r][i] = true;
            cols[c][i] = true;
            g[r][c] = i;
            // if(DEBUG && gn == 4){
            //     display();
            // }
            bool c1 = false;
            if(!(gn == ngn && gv[gn] == 0) && !(gn != ngn && gv[gn] != 0)) c1 = solve(ngn, nidx);
            if (c1)
                return true;
            g[r][c] = 0;
            rows[r][i] = false;
            cols[c][i] = false;
            gv[gn] += i;
        }
    }
    else if (go[gn] == 3) // *
    {
        rep(i, 1, n + 1)
        {
            if (rows[r][i] || cols[c][i] || gv[gn] % i != 0)
                continue;
            gv[gn] /= i;
            rows[r][i] = true;
            cols[c][i] = true;
            g[r][c] = i;
            // if(DEBUG) cout << "trying " << i << " at " << r << "," << c << " left: " << gv[gn] << " " << ngn << " " << nidx << nL;
            bool c1 = false;
            if(!(ngn != gn && gv[gn] != 1)) c1 = solve(ngn, nidx);
            if (c1)
                return true;
            g[r][c] = 0;
            rows[r][i] = false;
            cols[c][i] = false;
            gv[gn] *= i;
        }
    }
    else if (go[gn] == 2) // -
    {
        if(idx + 1 >= sz(groups[gn])) return false;
        auto [r1, c1] = groups[gn][idx + 1];
        rep(i, 1, n + 1)
        {
            int j = gv[gn] + i;
            if(j > n) break;
            // adjacent equal not possible by problem design, which is why we check one by one if it breaks uniqueness
            if (rows[r][i] == 0 && cols[c][i] == 0)
            {
                rows[r][i] = cols[c][i] = true;
                if (rows[r1][j] == 0 && cols[c1][j] == 0)
                {
                    rows[r1][j] = cols[c1][j] = true;
                    g[r][c] = i, g[r1][c1] = j;
                    bool c2 = solve(gn + 1, 0);
                    if (c2)
                        return true;
                    g[r][c] = g[r1][c1] = 0;
                    rows[r1][j] = cols[c1][j] = false;
                }
                rows[r][i] = cols[c][i] = false;
            }
            if (rows[r][j] == 0 && cols[c][j] == 0)
            {
                rows[r][j] = cols[c][j] = true;
                if (rows[r1][i] == 0 && cols[c1][i] == 0)
                {
                    rows[r1][i] = cols[c1][i] = true;
                    g[r][c] = j, g[r1][c1] = i;
                    bool c2 = solve(gn + 1, 0);
                    if (c2)
                        return true;
                    g[r][c] = g[r1][c1] = 0;
                    rows[r1][i] = cols[c1][i] = false;
                }
                rows[r][j] = cols[c][j] = false;
            }
        }
    }
    else if (go[gn] == 4) // /
    {
        if(idx + 1 >= sz(groups[gn])) return false;
        auto [r1, c1] = groups[gn][idx + 1];
        rep(i, 1, n + 1)
        {
            int j = gv[gn] * i;
            if(j > n) break;
            if (rows[r][i] == 0 && cols[c][i] == 0)
            {
                rows[r][i] = cols[c][i] = true;
                if (rows[r1][j] == 0 && cols[c1][j] == 0)
                {
                    rows[r1][j] = cols[c1][j] = true;
                    g[r][c] = i, g[r1][c1] = j;
                    bool c2 = solve(gn + 1, 0);
                    if (c2)
                        return true;
                    g[r][c] = g[r1][c1] = 0;
                    rows[r1][j] = cols[c1][j] = false;
                }
                rows[r][i] = cols[c][i] = false;
            }
            if (rows[r][j] == 0 && cols[c][j] == 0)
            {
                rows[r][j] = cols[c][j] = true;
                if (rows[r1][i] == 0 && cols[c1][i] == 0)
                {
                    rows[r1][i] = cols[c1][i] = true;
                    g[r][c] = j, g[r1][c1] = i;
                    bool c2 = solve(gn + 1, 0);
                    if (c2)
                        return true;
                    g[r][c] = g[r1][c1] = 0;
                    rows[r1][i] = cols[c1][i] = false;
                }
                rows[r][j] = cols[c][j] = false;
            }
        }
    }

    return false;
}

signed main()
{
    // if(!DEBUG)
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    auto getgn = [](char c) -> int
    {
        if (c >= 'a' && c <= 'z')
            return c - 'a';
        return c - 'A' + 26;
    };
    int cn = 0;
    while (true)
    {
        cin >> n;
        mxr = -1;
        if (n == 0)
            break;
        // g = vvi(n, vi(n));
        // rows = vvi(n, vi(n + 1));
        // cols = vvi(n, vi(n + 1));
        memset(rows, 0, sizeof rows);
        memset(cols, 0, sizeof cols);
        memset(g, 0, sizeof g);

        cin >> ng;
        // gv = vl(ng);
        memset(gv, 0, sizeof gv);
        memset(go, 0, sizeof go);
        // go = vi(ng);
        groups = vector<vpi>(maxg);
        map<char, int> os;
        os['.'] = 0;
        os['+'] = 1;
        os['-'] = 2;
        os['*'] = 3;
        os['/'] = 4;
        rep(i, 0, n)
        {
            string str;
            cin >> str;
            rep(j, 0, n)
            {
                int gn = getgn(str[j]);
                groups[gn].pb({i, j});
                // if(DEBUG) cout << "insert " << i << "," << j << " into " << gn << nL;
            }
        }
        rep(i, 0, ng)
        {
            char c;
            ll a;
            char s;
            cin >> c >> a >> s;
            // if(DEBUG) cout << c << " " << a << " " << s << nL;
            int gn = getgn(c);
            gv[gn] = a;
            go[gn] = os[s];
            if (go[gn] == 0 && gv[gn] >= 1 && gv[gn] <= n && sz(groups[gn]) >= 1)
            {
                g[groups[gn][0].f][groups[gn][0].s] = gv[gn];
                rows[groups[gn][0].f][gv[gn]] = true;
                cols[groups[gn][0].s][gv[gn]] = true;
            }
        }
        bool c1 = solve(0, 0);
        cout << "KenKen Puzzle #" << (cn + 1) << ":\n";
        if (c1)
        {
            display();
        }
        cout << nL;
        // if (!DEBUG)
        //     assert(c1);
        cn++;
    }

    return 0;
}
