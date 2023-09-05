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

const ll inf = 1e9;

struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi, mset = inf;
    ll val = -inf;
    Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
    ll query(int L, int R)
    {
        if (R <= lo || hi <= L)
            return -inf;
        if (L <= lo && hi <= R)
            return val;
        push();
        return l->query(L, R) + r->query(L, R);
    }
    void set(int L, int R, int x = 1)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            mset = x;
            val = x * (hi - lo);
        }
        else
        {
            push(), l->set(L, R, x), r->set(L, R, x);
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
        if (mset != inf)
            l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
    }
};
// struct Node2 {
// 	Node2 *l = 0, *r = 0;
// 	int lo, hi;
//     ll val = 0;
//     Node *tree = 0;

// 	Node2(int lo, int hi, int miny, int maxy) : lo(lo), hi(hi) {
//         tree = new Node(miny, maxy);
// 		if (lo + 1 < hi) {
// 			int mid = lo + (hi - lo)/2;
// 			l = new Node2(lo, mid, miny, maxy); r = new Node2(mid, hi, miny, maxy);
// 		}
// 	}
// 	ll query(int L, int R, int YL, int YR) {
// 		if (R <= lo || hi <= L) return 0;
// 		if (L <= lo && hi <= R) return tree->query(YL, YR);
// 		push();
// 		return l->query(L, R, YL, YR) + r->query(L, R, YL, YR);
// 	}
// 	void set(int L, int R, int YL, int YR, int x=1) {
// 		if (R <= lo || hi <= L) return;
// 		if (L <= lo && hi <= R) {
//             tree->set(YL, YR, x);

//         }
// 		else {
// 			push(), l->set(L, R, YL, YR, x), r->set(L, R, YL, YR, x);
// 			val = l->val + r->val;
// 		}
// 	}
// 	void push() {
// 		if (!l) {
// 			int mid = lo + (hi - lo)/2;
// 			l = new Node2(lo, mid); r = new Node2(mid, hi);
// 		}
// 		if (mset != inf)
// 			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
// 		else if (madd)
// 			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
// 	}
// };

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    return 0;
}
