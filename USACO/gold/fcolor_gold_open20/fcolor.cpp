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

vvi parent, child;
queue<int> q;
struct UF
{
    vi e;
    vvi repr;
    UF(int n) : e(n, -1), repr(n) {
        rep(i, 0, n){
            repr[i].pb(i);
        }
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (repr[a].size() < repr[b].size())
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        for (int k : repr[b])
        {
            repr[a].pb(k);
        }
        for(int k : child[b]){
            child[a].pb(k);
        }
        child[b].clear();
        repr[b].clear();
        if(child[a].size() > 1) q.push(a);
        // if(child[b].size() > 0) child[a].pb(child[b][0]);
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    parent.resize(n);
    child.resize(n);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        parent[b].pb(a);
        child[a].pb(b);
    }
    
    // rep(i, 0, n)
    // {
    //     rep(j, 1, parent[i].size())
    //     {
    //         q.push({parent[i][0], parent[i][j]});
    //     }
    // }
    rep(i, 0, n)
    {
        if(child[i].size() > 1) q.push(i);
    }
    // check what self-loop does

    UF dsu(n);
    while (!q.empty())
    {
        int k = q.front();
        if(child[k].size() <= 1){
            q.pop();
            continue;
        }
        
        int c1 = child[k].back();
        child[k].pop_back();
        int c2 = child[k].back();
        if(dsu.sameSet(c1, c2)) continue;
        dsu.join(c1, c2);

        // if (dsu.join(p.f, p.s))
        // {
        //     if (parent[p.f].size() > 0 && parent[p.s].size() > 0)
        //     {
        //         q.push({parent[p.f][0], parent[p.s][0]});
        //     }
        //     // if (child[p.f].size() > 0 && child[p.s].size() > 0)
        //     // {
        //     //     q.push({child[p.f][0], child[p.s][0]});
        //     // }
        // }
    }
    vi ans(n, -1);
    int col = 1;
    rep(i, 0, n)
    {
        if(ans[dsu.find(i)] == -1) ans[i] = ans[dsu.find(i)] = col++;
        else ans[i] = ans[dsu.find(i)];
        cout << ans[i] << nL;
    }

    return 0;
}