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
    int L, R, mid;
    int val;

    Tree *left, *right;

    Tree(int l, int r)
    {
        L = l;
        R = r;
        mid = (L + R) / 2;
        val = 0;
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
            val = nval;
            return;
        }
        left->update(idx, nval);
        right->update(idx, nval);
        val = left->val + right->val;
    }

    int query(int l, int r){
        if(r < L || R < l) return 0;
        if(l <= L && R <= r) return val;
        return left->query(l, r) + right->query(l, r);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    return 0;
}