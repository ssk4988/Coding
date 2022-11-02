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

int n, m, q;
vi parent;
vvi adj;
vi depth;
vvi children;
vi label;
vector<vector<pair<int, pair<ll, ll>>>> jump(32, vector<pair<int, pair<ll, ll>>>());
vl offset;

void dfs(vector<bool> &visited, int cur, int d)
{
    visited[cur] = true;
    depth[cur] = d;
    for (int k : adj[cur])
    {
        if (visited[k])
            continue;
        parent[k] = cur;
        children[cur].pb(k);
        dfs(visited, k, d + 1);
    }
}

ll mod(ll k)
{
    return k % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m >> q;
    adj = vvi(n, vi());
    children = vvi(n, vi());
    parent = vi(n, -1);
    depth = vi(n, -1);

    offset.pb(1);
    rep(i, 0, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].pb(b);
        adj[b].pb(a);
        offset.pb(mod(offset[offset.size() - 1] * 10));
    }
    rep(i, 0, n)
    {
        int a;
        cin >> a;
        label.pb(a);
    }
    vector<bool> v(n, false);
    dfs(v, 0, 0);
    rep(i, 0, 32)
    {
        jump[i] = vector<pair<int, pair<ll, ll>>>(n, mp(-1, mp(-1, -1))); // f: node, s: path
        if (i == 0)
        {
            rep(j, 0, n)
            {
                if (parent[j] != -1)
                {
                    jump[i][j] = mp(parent[j], mp(label[j], label[j]));
                }
            }
        }
        else
        {
            bool jmp = false;
            rep(j, 0, n)
            {
                if (jump[i - 1][j].f != -1 && jump[i - 1][jump[i - 1][j].f].f != -1)
                {
                    jmp = true;
                    int snd = jump[i - 1][j].f;
                    jump[i][j] = mp(jump[i - 1][snd].f,
                                    mp(
                                        mod(mod(jump[i - 1][j].s.f * offset[1 << (i - 1)]) + jump[i - 1][snd].s.f),
                                        mod(mod(jump[i - 1][snd].s.s * offset[1 << (i - 1)]) + jump[i - 1][j].s.s)));
                }
            }
            if (!jmp)
                break;
        }
    }
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        ll l = 0, r = 0;
        int rcnt = 0;
        bool ladv = false, radv = false;
        while (depth[a] > depth[b])
        {
            int adv = 0;
            int dif = depth[a] - depth[b];
            while ((1 << (adv + 1)) <= dif)
            {
                adv++;
            }
            l = mod(mod(offset[1 << adv] * l) + jump[adv][a].s.f);
            a = jump[adv][a].f;
            ladv = true;
        }
        while (depth[a] < depth[b])
        {
            int adv = 0;
            int dif = depth[b] - depth[a];
            while ((1 << (adv + 1)) <= dif)
            {
                adv++;
            }
            r = mod(mod(offset[rcnt] * jump[adv][b].s.s) + r);
            rcnt += 1 << adv;
            b = jump[adv][b].f;
            radv = true;
        }
        while (a != b)
        {
            int adv = 0;
            while (jump[adv + 1][a].f != -1 && jump[adv + 1][a].f != jump[adv + 1][b].f)
            {
                adv++;
            }
            l = mod(mod(offset[1 << adv] * l) + jump[adv][a].s.f);
            a = jump[adv][a].f;
            r = mod(mod(offset[rcnt] * jump[adv][b].s.s) + r);
            rcnt += 1 << adv;
            b = jump[adv][b].f;
            radv = ladv = true;
        }
        ll ans = 0;
        if (ladv)
        {
            ans = l;
        }
        ans = mod(mod(offset[1] * ans) + label[a]);
        ans = mod(offset[rcnt] * ans);
        if (radv)
        {
            ans = mod(ans + r);
        }
        cout << ans << nL;
    }

    return 0;
}