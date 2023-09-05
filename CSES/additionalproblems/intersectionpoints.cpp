#include <bits/stdc++.h>
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
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, val = 0, madd = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {}
    int combine(int l, int r){
        return l + r;
    }
    void comb(){
        val = combine(l->val, r->val);
    }
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return combine(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			comb();
		}
	}
	void push() {
        if(!l){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r= new Node(mid, hi);
        }
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vvi pts(n, vi(4));
    set<int> ys;
    rep(i, 0, n)
    {
        rep(j, 0, 4)
        {
            cin >> pts[i][j];
            if(j % 2 == 1) ys.insert(pts[i][j]);
        }
    }
    unordered_map<int, int> ry;
    for(int i : ys) ry[i] = sz(ry);
    vector<array<int, 3>> events;
    rep(i, 0, n){
        pts[i][1] = ry[pts[i][1]];
        pts[i][3] = ry[pts[i][3]];
        if(pts[i][1] == pts[i][3]){
            events.pb({pts[i][0], 0, i});
            events.pb({pts[i][2], 2, i});
        }
        else{
            events.pb({pts[i][0], 1, i});
        }
    }
    sort(all(events));
    Node tree(0, sz(ry) + 5);
    ll ans = 0;
    for(auto [x, t, q] : events){
        if(t == 0){
            tree.add(pts[q][1], pts[q][1] + 1, 1);
        }
        if(t == 2){
            tree.add(pts[q][1], pts[q][1] + 1, -1);
        }
        if(t == 1){
            ans += tree.query(pts[q][1], pts[q][3] + 1);
        }
    }
    cout << ans << nL;

    return 0;
}
