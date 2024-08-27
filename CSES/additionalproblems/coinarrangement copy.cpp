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

const int inf = 1e9;
struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi, madd = 0, val = 0;
    bool reset = false;
    Node(int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
            val = l->val + r->val;
        }
    }
    int query(int L, int R)
    {
        if (R <= lo || hi <= L)
            return 0;
        if (L <= lo && hi <= R)
            return val;
        push();
        return l->query(L, R) + r->query(L, R);
    }
    void add(int L, int R, int x)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            madd += x;
            val += x;
        }
        else
        {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = l->val + r->val;
        }
    }
    void clear(int L, int R)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            reset = true;
            madd = 0;
        }
        else
        {
            push(), l->clear(L, R), r->clear(L, R);
            val = l->val + r->val;
        }
    }
    void push()
    {
        if (!l)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (reset)
            l->clear(lo, hi), r->clear(lo, hi), reset = false;
        if (madd)
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vvi grid(2, vi(n));
    vi rows(2), cols(n);
    rep(i, 0, 2)
    {
        rep(j, 0, n)
        {
            cin >> grid[i][j];
            rows[i] += grid[i][j];
            cols[j] += grid[i][j];
        }
    }
    vector<vector<Node *>> tree(2, vector<Node *>(2));
    set<int> up, down;
    // dim 0: row
    // dim 1: 0 left 1 right
    rep(i, 0, 2)
    {
        rep(j, 0, 2)
        {
            tree[i][j] = new Node(0, n);
        }
    }
    ll ans = 0;
    priority_queue<pi, vpi, greater<>> give, take;
    rep(i, 0, n)
    {
        while (grid[0][i] + grid[1][i] > 2)
        {
            int remrow = grid[0][i] ? 0 : 1;
            grid[remrow][i]--;
            if (sz(take))
            {
                auto [r, c] = take.top();
                take.pop();
                tree[remrow][0]->add(c, i, 1);
                ans += abs(c - i);
            }
            else
            {
                give.push({remrow, i});
            }
        }
        while (grid[0][i] + grid[1][i] < 2)
        {
            if (sz(give))
            {
                auto [r, c] = give.top();
                give.pop();
                grid[r][i]++;
                tree[r][1]->add(c, i, 1);
                ans += abs(c - i);
            }
            else
            {
                take.push({0, i});
                grid[0][i]++;
            }
        }
    }
    rep(i, 0, n)
    {
        assert(grid[0][i] + grid[1][i] == 2);
        if (grid[0][i] == 2)
        {
            down.insert(i);
            ans++;
        }
        else if (grid[1][i] == 2)
            up.insert(i), ans++;
        grid[0][i] = grid[1][i] = 1;
    }
    auto clockwise = [&](int lidx, int ridx) -> void
    {
        int sum = tree[0][1]->query(lidx, ridx) + tree[1][0]->query(lidx, ridx);
        if (2 * (2 + sum) > 2 * (1 + ridx - lidx))
        {
            ans -= 2 * (2 + sum) - 2 * (1 + ridx - lidx);
            tree[0][1]->clear(lidx, ridx);
            tree[1][0]->clear(lidx, ridx);
        }
        up.erase(lidx);
        down.erase(ridx);
    };
    auto check = [&](int idx, auto &&check) -> void
    {
        if (!up.count(idx) && !down.count(idx))
            return;
        bool isup = up.count(idx);
        auto it = (isup ? down : up).upper_bound(idx);
        if (isup)
        {
            if (it != down.end())
            {
                int ridx = *it;
                int sum = tree[0][1]->query(idx, ridx) + tree[1][0].query(idx, ridx);
                if (2 * (2 + sum) > 2 * (1 + ridx - idx))
                {
                    ans -= 2 * (2 + sum) - 2 * (1 + ridx - idx);
                    tree[0][1]->clear(idx, ridx);
                    tree[1][0]->clear(idx, ridx);
                }
            }
        }
    };

    cout << ans << "\n";

    return 0;
}
