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

vector<unordered_set<int>> adj;
ll ans = 0;

void solve(unordered_set<int> component)
{
    int minFriends = INT_MAX;
    for (int i : component)
    {
        minFriends = min(minFriends, (int)adj[i].size());
    }
    ans = max(minFriends * (ll)component.size(), ans);
    deque<int> rem;
    vi r;
    for (int i : component)
    {
        if (adj[i].size() <= minFriends)
        {
            rem.pb(i);
            r.pb(i);
        }
    }
    for (int i : r)
    {
        component.erase(component.find(i));
    }
    while (rem.size())
    {
        int i = rem.front();
        rem.pop_front();
        for (int j : adj[i])
        {
            adj[j].erase(adj[j].find(i));
            if (component.find(j) != component.end() && adj[j].size() <= minFriends)
            {
                component.erase(component.find(j));
                rem.pb(j);
            }
        }
        adj[i].clear();
    }
    unordered_set<int> removed;
    for (int i : component)
    {
        if (removed.find(i) != removed.end())
            continue;
        unordered_set<int> newcomp;
        deque<int> q;
        newcomp.insert(i);
        removed.insert(i);
        q.pb(i);
        while (q.size())
        {
            int k = q.front();
            q.pop_front();
            for (int l : adj[k])
            {
                if (newcomp.find(l) == newcomp.end())
                {
                    newcomp.insert(l);
                    removed.insert(l);
                    q.pb(l);
                }
            }
        }
        solve(newcomp);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    unordered_set<int> tot;
    rep(i, 0, n)
    {
        tot.insert(i);
    }
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    rep(i, 0, n)
    {
        if (tot.find(i) == tot.end())
        {
            continue;
        }
        unordered_set<int> component;
        deque<int> q;
        component.insert(i);
        tot.erase(tot.find(i));
        q.pb(i);
        while (q.size())
        {
            int k = q.front();
            q.pop_front();
            for (int l : adj[k])
            {
                if (component.find(l) == component.end())
                {
                    component.insert(l);
                    tot.erase(tot.find(l));
                    q.pb(l);
                }
            }
        }
        solve(component);
    }
    cout << ans << nL;
    return 0;
}