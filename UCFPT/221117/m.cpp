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
    int n;
    cin >> n;
    map<string, int> m;
    map<int, string> rev;
    vvi edges;
    string stuff;
    getline(cin, stuff);
    rep(i, 0, n)
    {
        // cout << i << " ";
        getline(cin, stuff);
        // cout << stuff << nL;
        stringstream c(stuff);
        string first;
        vi nodes;
        while (c >> first)
        {
            if (m.find(first) == m.end())
            {
                m[first] = m.size();
                edges.pb({});
            }
            nodes.pb(m[first]);
            // cout << "read " << m[first] << " ";
        }
        // cout << nL;
        rep(i, 1, nodes.size())
        {
            edges[nodes[0]].pb(nodes[i]);
            edges[nodes[i]].pb(nodes[0]);
        }
    }
    string f;
    cin >> f;
    if (m.find(f) == m.end())
    {
        m[f] = m.size();
        edges.pb({});
    }
    int start = m[f];
    cin >> f;
    if (m.find(f) == m.end())
    {
        m[f] = m.size();
        edges.pb({});
    }
    int end = m[f];
    vi order;
    vector<bool> visited(m.size(), false);
    vi ans;
    auto dfs = [&](int cur, auto &&dfs) -> void
    {
        if (visited[cur])
            return;
        visited[cur] = true;
        order.pb(cur);
        if (cur == end)
        {
            ans = order;
        }
        for (int k : edges[cur])
        {
            dfs(k, dfs);
        }
        order.erase(order.begin() + order.size() - 1);
        //visited[cur] = false;
    };
    dfs(start, dfs);
    for (auto &p : m)
    {
        rev[p.s] = p.first;
    }
    if (ans.size() > 0)
    {
        rep(i, 0, ans.size())
        {
            cout << rev[ans[i]] << " ";
        }
    }
    else
    {
        cout << "no route found";
    }

    cout << nL;

    return 0;
}