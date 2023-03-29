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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int k;
    cin >> k;
    int maxN = 1000;
    vvi adj(maxN);
    int nodesUsed = 2;
    int maxbit = 0;
    map<int, vi> nodeconnect;
    rep(i, 0, 31)
    {
        if (((1 << i) & k) > 0)
        {
            maxbit = i;
        }
    }
    auto connect = [&](int a, int b) -> void
    {
        adj[a].pb(b);
        adj[b].pb(a);
    };
    if (maxbit == 0)
    {
        connect(0, 1);
    }
    else
    {
        nodeconnect[0].pb(1);
        rep(i, 0, maxbit)
        {
            if (i == 0)
            {
                connect(nodesUsed++, 1);
                connect(nodesUsed++, 1);
            }
            else
            {
                connect(nodesUsed, nodesUsed - 1);
                connect(nodesUsed, nodesUsed - 2);
                connect(nodesUsed + 1, nodesUsed - 1);
                connect(nodesUsed + 1, nodesUsed - 2);
                nodesUsed += 2;
            }
            nodeconnect[i + 1].pb(nodesUsed - 1);
            nodeconnect[i + 1].pb(nodesUsed - 2);
        }
        // connect(0, nodesUsed - 1);
        // connect(0, nodesUsed - 2);
        int offset = nodesUsed;
        int cur = 0;
        map<int, int> fir;
        fir[maxbit] = 0;
        rep(i, 0, maxbit)
        {
            fir[maxbit - i - 1] = nodesUsed;
            connect(cur, nodesUsed++);
            cur = nodesUsed - 1;
        }
        rep(i, 0, maxbit + 1)
        {
            if (((1 << i) & k) > 0)
            {
                for(int j : nodeconnect[i]){
                    connect(fir[i], j);
                }
            }
        }
    }
    vvi adjmat(nodesUsed, vi(nodesUsed));
    rep(i, 0, nodesUsed){
        for(int j : adj[i]){
            adjmat[i][j] = 1;
        }
    }
    cout << nodesUsed << nL;
    rep(i, 0, nodesUsed){
        rep(j, 0, nodesUsed){
            cout << (adjmat[i][j] ? "Y" : "N");
        }
        cout << nL;
    }

    return 0;
}
