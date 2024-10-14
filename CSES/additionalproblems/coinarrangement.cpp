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
            cin >> grid[i][j]; grid[i][j]--;
        }
    }
    vi net(2);
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, 2) net[j] += grid[j][i];
        if(net[0] > 0 && net[1] <= 0 || net[0] <= 0 && net[1] > 0) {
            int mn = min(abs(net[0]), abs(net[1]));
            if(net[0] > 0 && net[1] <= 0) {
                net[0] -= mn, net[1] += mn;
            } else net[0] += mn, net[1] -= mn;
            ans += mn;
        }
        ans += abs(net[0]) + abs(net[1]);
    }
    cout << ans << "\n";

    return 0;
}
