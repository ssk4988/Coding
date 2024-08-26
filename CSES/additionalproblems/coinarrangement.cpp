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
    int n; cin >> n;
    vvi grid(2, vi(n));
    rep(i, 0, 2)
    {
        rep(j, 0, n)
        {
            cin >> grid[i][j];
        }
    }
    ll ans = 0;
    priority_queue<pi, vpi, greater<>> give, take;
    vector<vpi> add(n), rem(n);
    // 0 up 1 down
    int ids = 0;
    vpi intervals;
    rep(i, 0, n)
    {
        while (grid[0][i] + grid[1][i] > 2)
        {
            int remrow = grid[0][i] > 1 ? 0 : 1;
            grid[remrow][i]--;
            if (sz(take))
            {
                auto [r, c] = take.top();
                take.pop();
                if(r != remrow) {
                    add[c].pb({r < remrow, ids});
                    rem[i].pb({r < remrow, ids});
                    intervals.pb({c, i});
                    ids++;
                }
                ans += abs(c - i) + abs(remrow - r);
            }
            else
            {
                give.push({remrow, i});
            }
        }
        while (grid[0][i] + grid[1][i] < 2)
        {
            int addrow = grid[0][i] < 1 ? 0 : 1;
            grid[addrow][i]++;
            if (sz(give))
            {
                auto [r, c] = give.top();
                give.pop();
                if(r != addrow) {
                    add[c].pb({r < addrow, ids});
                    rem[i].pb({r < addrow, ids});
                    intervals.pb({c, i});
                    ids++;
                }
                ans += abs(c - i) + abs(r - addrow);
            }
            else
            {
                take.push({addrow, i});
            }
        }
    }
    set<pi> up, down;
    rep(i, 0, n)
    {
        assert(grid[0][i] + grid[1][i] == 2);
        if(grid[0][i] != 1) {
            ans++;
            grid[0][i] = grid[1][i] = 1;
        }
    }
    rep(i, 0, n){
        for(auto [isdown, id] : add[i]) {
            if(isdown && sz(up)){
                auto [endp, id1] = *up.begin();
                up.erase(up.begin());
                ans -= 2;
            } else if(!isdown && sz(down)) {
                auto [endp, id1] = *down.begin();
                down.erase(down.begin());
                ans -= 2;
            } else {
                (isdown ? down : up).insert({intervals[id].s, id});
            }
        }
        for(auto [isdown, id] : rem[i]) {
            if((isdown ? down : up).count({i, id})) {
                (isdown ? down : up).erase({i, id});
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
