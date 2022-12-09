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

#define maxN 200000

pl pows[maxN];
pl m = {1000000007, 1000000009};
ll base = 29;

ll mod1(ll k, ll m1){
    return (k % m1 + m1) % m1;
}

pl mod(pl k){
    return {mod1(k.f, m.f), mod1(k.s, m.s)};
}

struct Tree
{
    int L, R, mid, len;
    pl val;

    Tree *left, *right;

    Tree(int l, int r)
    {
        L = l;
        R = r;
        mid = (L + R) / 2;
        val = {0, 0};
        len = R - L + 1;
        if (L == R)
            return;
        left = new Tree(l, mid);
        right = new Tree(mid + 1, r);
    }

    void update(int idx, int nval)
    {
        if (idx < L || R < idx)
            return;
        if (L == R)
        {
            val = mod({nval, nval});
            return;
        }
        left->update(idx, nval);
        right->update(idx, nval);
        val = mod({pows[left->len].f * right->val.f, pows[left->len].s * right->val.s});
        val = mod({left->val.f + val.f, left->val.s + val.s});
    }

    pl query(int l, int r){
        if(r < L || R < l) return {0, 0};
        if(l <= L && R <= r) return val;
        pl lres = left->query(l, r);
        pl rres = right->query(l, r);
        int llen = left->R < l || r < left->L ? 0 : min(left->R, r) - max(left->L, l) + 1;
        pl res = mod({pows[llen].f * rres.f, pows[llen].s * rres.s});
        res = mod({lres.f + res.f, lres.s + res.s});
        return res;
    }
};
int n;

int revindex(int k){
    return n - 1 - k;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> n >> q;
    pows[0] = {1, 1};
    rep(i, 1, n){
        pows[i] = mod({pows[i - 1].f * base, pows[i - 1].s * base});
    }
    Tree tree(0, n - 1);
    Tree revtree(0, n - 1);
    string str; cin >> str;
    rep(i, 0, n){
        tree.update(i, str[i] - 'a' + 1);
        revtree.update(i, str[revindex(i)] - 'a' + 1);
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int ind;
            char c;
            cin >> ind >> c;
            ind--;
            tree.update(ind, c - 'a' + 1);
            revtree.update(revindex(ind), c - 'a' + 1);
        }
        else{
            int a, b;
            cin >> a >> b;
            a--; b--;
            cout << ((tree.query(a, b) == revtree.query(revindex(b), revindex(a))) ? "YES" : "NO") << nL;
        }
    }

    
    return 0;
}