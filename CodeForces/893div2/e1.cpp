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

const int n = 1e6 + 10;
const int b = 21;
vi children[n];
int add[n];
vi queries[n];
int jmp[n][b];


map<int, int> ft;
int un = -1;
vi ans;
void dfs(int cur)
{
    // sort(all(queries[cur]));
    if(ft[add[cur]] == 0) un++;
    ft[add[cur]]++;
    for (auto x : queries[cur])
    {
        ans[x] = un;
    }
    for (auto nex : children[cur])
    {
        dfs(nex);
    }
    ft[add[cur]]--;
    if(ft[add[cur]] == 0) un--;
}
int used = 0;
void createNode(int par = 0){
    jmp[used][0] = par;
    rep(i, 1, b) jmp[used][i] = jmp[jmp[used][i - 1]][i - 1];
    used++;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    createNode();
    add[0] = -1;
    vi updates;
    updates.pb(0);
    int qs = 0;
    rep(i, 0, q)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int x;
            cin >> x;
            int u = used;
            createNode(updates.back());
            add[u] = x;
            children[updates.back()].pb(u);
            updates.pb(u);
        }
        if (c == '-')
        {
            int k;
            cin >> k;
            int cur = updates.back();
            for(int j = 20; j >= 0; j--){
                if(k & (1 << j)) cur = jmp[cur][j];
            }
            updates.pb(cur);
        }
        if (c == '!')
            updates.pop_back();
        if (c == '?')
        {
            // cout << updates.back()->r->sum1 << nL;
            queries[updates.back()].pb(qs++);
        }
    }
    ans.assign(qs, -1);

    dfs(0);
    rep(i, 0, qs)
    {
        if (ans[i] != -1)
            cout << ans[i] << nL;
    }
    // cout << inited << nL;

    return 0;
}
