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

vi num, st;
vector<vector<pi>> ed;
int Time;
template <class F>
int dfs(int at, int par, F &f)
{
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at])
        if (pa.second != par)
        {
            tie(y, e) = pa;
            if (num[y])
            {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.push_back(e);
            }
            else
            {
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up < me)
                    st.push_back(e);
                else
                { // (up == me) {
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                }
                // else { /* e is a bridge */}
            }
        }
    return top;
}

int n, m, qu;
vvi grid;
vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int encode(pi v)
{
    auto [r, c] = v;
    return r * m + c;
}
pi decode(int v)
{
    return {v / m, v % m};
}
int numedges = 0;
struct edge
{
    int a, b;
    int eid = -1;
    int bccid = -1;
};
// vector<edge *> edges;
edge edges[1500 * 1500 * 4];

// struct node
// {
//     int r, c;
//     int ec;
//     vector<edge *> adj = {NULL, NULL, NULL, NULL};
//     node() {}
// };

// vector<node *> nodes;
int ngrid[1500][1500][4];
bool dp[1500 * 1500][4];
// unordered_map<int, node *> nmap;
int numbcc = 0, numco = 0;
bool inrange(pi v)
{
    if (v.f < 0 || v.s < 0 || v.f >= n || v.s >= m)
        return false;
    return true;
}

void func(vi eset)
{
    // // cout << at << nL;
    // art[at] = true;
    for (int i : eset)
    {
        edges[i].bccid = numbcc;
    }
    numbcc++;
}

queue<pi> q;
bool used[1500 * 1500];
void bessdfs(int cur)
{
    if (used[cur])
        return;
    used[cur] = true;
    pi cc = decode(cur);
    rep(k, 0, 4)
    {
        pi v = {cc.f + ds[k][0], cc.s + ds[k][1]};
        if (!inrange(v) || grid[v.f][v.s] == 1)
            continue;
        if (grid[v.f][v.s] == 3)
        {
            pi q1 = {encode(v), (k + 2) % 4};
            q.push(q1);
        }
        else if (!used[encode(v)])
        {
            bessdfs(encode(v));
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // freopen("pushabox.in", "r", stdin);
    // freopen("pushabox.out", "w", stdout);
    cin >> n >> m >> qu;
    grid = vvi(n, vi(m));
    rep(i, 0, n)
    {
        rep(j, 0, m)
        {
            rep(k, 0, 4)
            {
                ngrid[i][j][k] = -1;
            }
        }
    }
    int box = -1, bessie = -1;
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        rep(j, 0, m)
        {
            if (str[j] == '.')
            {
                grid[i][j] = 0;
            }
            else if (str[j] == '#')
            {
                grid[i][j] = 1;
            }
            else if (str[j] == 'A')
            {
                grid[i][j] = 2;
                bessie = encode({i, j});
            }
            else
            {
                grid[i][j] = 3; // B
                box = encode({i, j});
            }
        }
    }
    ed.resize(n * m);
    rep(i, 0, n)
    {
        rep(j, 0, m)
        {
            pi cc = {i, j};
            if (grid[i][j] != 1)
            {
                rep(k, 0, 4)
                {
                    if (ngrid[i][j][k] != -1)
                        continue;
                    pi v = {i + ds[k][0], j + ds[k][1]};
                    if (!inrange(v) || grid[v.f][v.s] == 1)
                    {
                        continue;
                    }
                    numedges++;
                    edge *e1 = &edges[numedges];
                    e1->eid = numedges;
                    e1->a = encode(cc), e1->b = encode(v);
                    ngrid[cc.f][cc.s][k] = e1->eid;
                    ngrid[v.f][v.s][(k + 2) % 4] = e1->eid;
                    ed[e1->a].pb({e1->b, e1->eid});
                    ed[e1->b].pb({e1->a, e1->eid});
                }
            }
        }
    }
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i] && grid[decode(i).f][decode(i).s] != 1)
        dfs(i, -1, func); // create function


    bessdfs(bessie);
    while (!q.empty())
    {
        pi state = q.front();
        q.pop();
        if (dp[state.f][state.s])
            continue;
        dp[state.f][state.s] = true;
        pi ij = decode(state.f);
        int invdir = (state.s + 2) % 4;
        pi pushb = {ij.f + ds[invdir][0], ij.s + ds[invdir][1]};
        if (inrange(pushb) && grid[pushb.f][pushb.s] != 1 && !dp[encode(pushb)][state.s])
        {
            q.push({encode(pushb), state.s});
        }
        rep(k, 0, 4)
        {
            pi s1 = decode(state.f);
            if (ngrid[s1.f][s1.s][k] != -1 && edges[ngrid[s1.f][s1.s][k]].bccid == edges[ngrid[s1.f][s1.s][state.s]].bccid && !dp[state.f][k])
            {
                q.push({state.f, k});
            }
        }
    }
    rep(i, 0, qu)
    {
        int r, c;
        cin >> r >> c;
        r--, c--;
        bool works = encode({r, c}) == box;
        rep(k, 0, 4) if (dp[encode({r, c})][k]) works = true;
        cout << (works ? "YES" : "NO") << nL;
    }

    return 0;
}
