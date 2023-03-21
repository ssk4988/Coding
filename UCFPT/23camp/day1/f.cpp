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

struct Tree
{
    Tree *left, *right;
    pi minval;
    int gcdval;
    int lo, hi, mid;
    Tree(vi &v, int L, int R)
    {
        lo = L;
        hi = R;
        if (L + 1 == R)
        {
            minval = {v[lo], 1};
            gcdval = v[lo];
        }
        else
        {
            mid = (L + R) / 2;
            left = new Tree(v, L, mid);
            right = new Tree(v, mid, R);
            minval = combmin(left->minval, right->minval);
            gcdval = gcd(left->gcdval, right->gcdval);
        }
    }
    pi combmin(pi l, pi r)
    {
        if (l.f < r.f)
        {
            return l;
        }
        else if (l.f > r.f)
        {
            return r;
        }
        else
        {
            return {l.f, l.s + r.s};
        }
    }
    // R is exclusive
    pi minq(int L, int R)
    {
        if (R <= lo || hi <= L)
        {
            return {INT_MAX, 0};
        }
        if (L <= lo && hi <= R)
        {
            return minval;
        }
        return combmin(left->minq(L, R), right->minq(L, R));
    }
    int gcdq(int L, int R)
    {
        if (R <= lo || hi <= L)
        {
            return -1;
        }
        if (L <= lo && hi <= R)
        {
            return gcdval;
        }
        int lgcd = left->gcdq(L, R), rgcd = right->gcdq(L, R);
        if(lgcd == -1) return rgcd;
        if(rgcd == -1) return lgcd;
        return gcd(rgcd, lgcd);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    Tree *root = new Tree(a, 0, n);
    int q; cin >> q;
    rep(i, 0, q){
        int l, r; cin >> l >> r;
        int gcdval = root->gcdq(l-1, r);
        pi minval = root->minq(l-1, r);
        int ans = r - l + 1 - (gcdval == minval.f ? minval.s : 0);
        cout << ans << nL;
    }
    return 0;
}
