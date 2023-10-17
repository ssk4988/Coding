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


const int maxg = 55;

int n, ng;
const int maxn = 15;
// vvi g;
int g[maxn][maxn];
int grp[maxn][maxn];
vector<vpi> groups;
ll gv[maxg]; // group value
int go[maxg]; // group operator
int rem[maxg];
vector<vvi> subs, divs;
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
bool solve(int r, int c)
{
    
    if (r == n)
    {
        return true;
    }
    int nr = r + (c == n - 1), nc = (c == n - 1 ? 0 : c + 1);
    int gn = grp[r][c];
    if(g[r][c]){
        return solve(nr, nc);
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
            rem[gn]--;
            // if(DEBUG && gn == 4){
            //     display();
            // }
            bool c1 = false;
            if(!(rem[gn] == 0 && gv[gn] > 0) && !(rem[gn] > gv[gn])) c1 = solve(nr, nc);
            if (c1)
                return true;
            rem[gn]++;
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
            rem[gn]--;
            // if(DEBUG) cout << "trying " << i << " at " << r << "," << c << " left: " << gv[gn] << " " << ngn << " " << nidx << nL;
            bool c1 = false;
            if(!(rem[gn] == 0 && gv[gn] > 1)) c1 = solve(nr, nc);
            if (c1)
                return true;
            rem[gn]++;
            g[r][c] = 0;
            rows[r][i] = false;
            cols[c][i] = false;
            gv[gn] *= i;
        }
    }
    else if (go[gn] == 2) // -
    {
        int preval = 0;
        if(rem[gn] == 1){
            for(auto [r1, c1] : groups[gn]){
                preval += g[r1][c1];
            }
            for(int val : subs[gv[gn]][preval]){
                if(rows[r][val] || cols[c][val]) continue;
                rows[r][val] = true;
                cols[c][val] = true;
                rem[gn]--;
                g[r][c] = val;
                bool c1 = solve(nr, nc);
                if(c1) return true;
                rem[gn]++;
                g[r][c] = 0;
                rows[r][val] = false;
                cols[c][val] = false;
            }
        }
        else{
            rep(i, 1, n + 1){
                if(sz(subs[gv[gn]][i]) == 0 || rows[r][i] || cols[c][i]) continue;
                rows[r][i] = true;
                cols[c][i] = true;
                rem[gn]--;
                g[r][c] = i;
                bool c1 = solve(nr, nc);
                if(c1) return true;
                rem[gn]++;
                g[r][c] = 0;
                rows[r][i] = false;
                cols[c][i] = false;
            }
        }
    }
    else if (go[gn] == 4) // /
    {
        int preval = 0;
        if(rem[gn] == 1){
            for(auto [r1, c1] : groups[gn]){
                preval += g[r1][c1];
            }
            for(int val : divs[gv[gn]][preval]){
                if(rows[r][val] || cols[c][val]) continue;
                rows[r][val] = true;
                cols[c][val] = true;
                rem[gn]--;
                g[r][c] = val;
                bool c1 = solve(nr, nc);
                if(c1) return true;
                rem[gn]++;
                g[r][c] = 0;
                rows[r][val] = false;
                cols[c][val] = false;
            }
        }
        else{
            rep(i, 1, n + 1){
                if(sz(divs[gv[gn]][i]) == 0 || rows[r][i] || cols[c][i]) continue;
                rows[r][i] = true;
                cols[c][i] = true;
                rem[gn]--;
                g[r][c] = i;
                bool c1 = solve(nr, nc);
                if(c1) return true;
                rem[gn]++;
                g[r][c] = 0;
                rows[r][i] = false;
                cols[c][i] = false;
            }
        }
    }

    return false;
}

int main()
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
        memset(rem, 0, sizeof rem);
        memset(grp, 0, sizeof grp);
        divs = vector<vvi>(100, vvi(n + 1));
        subs = vector<vvi>(100, vvi(n + 1));
        rep(i, 1, n + 1){
            rep(j, 1, i){
                subs[abs(i - j)][i].pb(j);
                subs[abs(i - j)][j].pb(i);
                if(i % j == 0){
                    divs[i / j][i].pb(j);
                    divs[i / j][j].pb(i);
                }
                else if(j % i == 0){
                    divs[j / i][i].pb(j);
                    divs[j / i][j].pb(i);
                }
            }
        }

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
                grp[i][j] = gn;
                groups[gn].pb({i, j});
                rem[gn]++;
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
