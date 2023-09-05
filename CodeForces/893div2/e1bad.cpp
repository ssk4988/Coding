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

struct Node
{
    vector<Node *> children;
    vpi queries;
    Node *par;
    vector<Node*> pars;
    Node(Node *p = NULL) : pars(21) {
        pars[0] = p == NULL ? this : p;
        rep(i, 1, 21){
            pars[i] = pars[i - 1]->pars[i - 1];
        }
    }
};

struct FT
{
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif)
    { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    ll query(int pos)
    { // sum of values in [0, pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
    int lower_bound(ll sum)
    { // min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
        {
            if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};
map<int, int> ft;
int un = 0;
vi ans;
void dfs(Node *cur)
{
    // sort(all(cur->queries));
    // vi seton;

    for (auto [t, x] : cur->queries)
    {
        if (t == 0)
        {
            if(ft[x] == 0) un++;
            ft[x]++;
        }
    }
    for (auto [t, x] : cur->queries)
    {
        if (t == 1)
        {
            ans[x] = un;
        }
    }
    for (auto nex : cur->children)
    {
        dfs(nex);
    }
    for (auto [t, x] : cur->queries)
    {
        if (t == 0)
        {
            ft[x]--;
            if(ft[x] == 0) un--;
        }
    }
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    Node *root = new Node();
    vector<Node *> updates;
    updates.pb(root);
    rep(i, 0, q)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int x;
            cin >> x;
            Node *n = new Node(updates.back());
            n->queries.pb({0, x - 1});
            updates.back()->children.pb(n);
            updates.pb(n);
        }
        if (c == '-')
        {
            int k;
            cin >> k;
            Node *cur = updates.back();
            for(int j = 20; j >= 0; j--){
                if(k & (1 << j)) cur = cur->pars[j];
            }
            updates.pb(cur);
        }
        if (c == '!')
            updates.pop_back();
        if (c == '?')
        {
            // cout << updates.back()->r->sum1 << nL;
            updates.back()->queries.pb({1, i});
        }
    }
    ans.assign(q, -1);

    dfs(root);
    rep(i, 0, q)
    {
        if (ans[i] != -1)
            cout << ans[i] << nL;
    }
    // cout << inited << nL;

    return 0;
}
