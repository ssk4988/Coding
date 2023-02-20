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

// assumes freq sum will not overflow int
int BLANK = 0;
struct Tree
{
    int L, R, mid;
    Tree *left, *right, *parent = NULL;
    int lazy = 0;
    pi val = {0, R - L + 1};

    Tree(int l, int r)
    {
        L = l;
        R = r;
        mid = (L + R) / 2;
        lazy = 0;
        val = {0, R - L + 1};
        if (L == R)
            return;

        left = new Tree(l, mid);
        left->parent = this;
        right = new Tree(mid + 1, r);
        right->parent = this;
    }

    void str()
    {
        cout << "range: " << L << " to " << R << " keys: {" << val.f << ", " << val.s
             << "}\n";
        if (L != R)
        {
            left->str();
            right->str();
        }
    }

    void prop()
    {
        if (lazy == BLANK)
            return;

        // val.f += lazy;

        if (L == R)
        {
            lazy = BLANK;
            return;
        }

        // left->prop();
        // right->prop();

        left->lazy += lazy;
        left->val.f += lazy;
        right->lazy += lazy;
        right->val.f += lazy;
        lazy = BLANK;
    }
    void recalc()
    {
        val = comb(left->val, right->val);
    }
    pi comb(pi l, pi r)
    {
        if (l.f == r.f)
        {
            return {l.f, l.s + r.s};
        }
        else if (l.f < r.f)
        {
            return l;
        }
        else
        {
            return r;
        }
    }

    pi query(int l, int r)
    {
        if (L > r || l > R)
            return {INT_MAX, 0};
        if (L >= l && R <= r)
        {
            return val;
        }
        else
        {
            prop();
            return comb(left->query(l, r), right->query(l, r));
        }
    }

    void update(int l, int r, int offset)
    {
        if (L > r || l > R)
            return;

        if (L >= l && R <= r)
        {
            lazy += offset;
            val.f += offset;
            return;
        }
        prop();
        left->update(l, r, offset);
        right->update(l, r, offset);
        recalc();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    vi a(n);
    int siz = 1'000'010;
    vvi occ(siz);
    vi freq(siz);
    rep(i, 0, n)
    {
        cin >> a[i];
        occ[a[i]].pb(i);
    }
    rep(i, 0, sz(occ))
    {
        occ[i].pb(n);
    }
    auto getrange = [&](int val) -> pi
    {
        if (sz(occ[val]) == 0)
            return {n, n};
        int l = occ[val][min(sz(occ[val]) - 1, freq[val] + k - 1)], r = max(l, occ[val][min(sz(occ[val]) - 1, freq[val] + k)] - 1);
        return {l, r};
    };

    Tree root(0, n);
    // root.str();
    ll ans = 0;
    rep(i, 0, sz(occ))
    {
        pi v = getrange(i);
        if(v.f < n) root.update(v.f, v.s, 1);
        // root.str();
    }
    rep(i, 0, n)
    {
        pi v = root.query(i, n - 1);
        if (v.f == 0)
            ans += v.s;
        if(i >= n - 1) break;
        v = getrange(a[i]);
        root.update(v.f, v.s, -1);
        freq[a[i]]++;
        v = getrange(a[i]);
        root.update(v.f, v.s, 1);
    }
    cout << ans << nL;

    return 0;
}
