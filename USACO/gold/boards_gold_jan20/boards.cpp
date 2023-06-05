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

const int inf = 1e9 + 10;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, p; cin >> n >> p;
    vector<pair<pi, pi>> v(p);
    set<int> ss;
    int maxn = 1e9 + 1;
    rep(i, 0, p){
        cin >> v[i].f.f >> v[i].s.f >> v[i].f.s >> v[i].s.s;
        ss.insert(v[i].s.f);
        ss.insert(v[i].s.s);
    }
    sort(all(v));
    Node *tree = new Node(0, maxn);
    tree->set(0, maxn, 0);
    set<vi> pq;
    int pnter = 0;
    auto cmp = [&](vi &event, pair<pi, pi> &jmp)->bool{
        if(event[0] == jmp.f.f){
            if(event[0] == jmp.f.s){
                return event[1] <= jmp.s.f;
            }
            return event[0] < jmp.f.s;
        }
        return event[0] < jmp.f.f;
    };
    while(pnter < p || pq.size()){
        vi p1 = (pq.size() ? *pq.begin() : vi(0));
        if(pnter >= p || (pq.size() && cmp(p1, v[pnter]))){
            tree->set(p1[1], p1[1] + 1, max(tree->query(p1[1], p1[1] + 1), p1[2]));
            pq.erase(pq.begin());
        }
        else{
            pq.insert({v[pnter].f.s, v[pnter].s.s, tree->query(0, v[pnter].s.f + 1) + (v[pnter].f.s - v[pnter].f.f) + (v[pnter].s.s - v[pnter].s.f)});
            pnter++;
        }
    }
    int ans = 2 * n - tree->query(0, maxn);
    cout << ans << nL;

    return 0;
}
