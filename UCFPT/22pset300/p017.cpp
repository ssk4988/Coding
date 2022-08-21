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
#define maxN 20

int n;
int root[maxN];
vi children[maxN];
int order[maxN];
int ind = 0;
set<int> s;

void dfs(int cur)
{
    order[ind++] = cur;
    for (int i : children[cur])
    {
        dfs(i);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n;

    root[0] = -1;
    rep(i, 1, n)
    {
        cin >> root[i];
    }

    rep(i, 1, n)
    {
        root[i]--;
        children[root[i]].pb(i);
    }
    dfs(0);
    int cur = 1;
    vi ans;
    while (true)
    {
        s.insert(cur);
        int cnt = s.size();
        rep(i, 1, n)
        {
            bool cond = true;
            if (cur & (1 << order[i]))
            {
                for (int i1 : children[order[i]])
                {
                    if (cur & (1 << i1))
                        cond = false;
                }
            }
            else
            {
                cond = cur & (1 << root[order[i]]);
            }
            if (cond)
            {
                cur ^= 1 << order[i];
                if (s.count(cur))
                {
                    cur ^= 1 << order[i];
                    continue;
                }
                s.insert(cur);
                ans.pb(order[i] + 1);
                break;
            }
        }
        if (cnt == s.size())
        {
            break;
        }
    }
    cout << ans.size() << nL;
    rep(i, 0, ans.size())
    {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}