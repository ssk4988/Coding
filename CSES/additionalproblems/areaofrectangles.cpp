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
	int lo, hi, madd = 0;
    pi val; // min, freq of min
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = comb(l->val, r->val);
		}
        else{
            val = {0, 1};
        }
	}
    pi comb(pi a, pi b){
        if(a.f == b.f){
            return {a.f, a.s + b.s};
        }
        return min(a, b);
    }
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return {inf, 0};
		if (L <= lo && hi <= R) return val;
		push();
		return comb(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
        // cout << "On segment " << lo << "," << hi << endl;
		if (L <= lo && hi <= R) {
			madd += x;
			val.f += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = comb(l->val, r->val);
		}
	}
	void push() {
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

using rect = pair<pi, pi>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    
    vector<rect> rs(n);
    vector<tuple<int, int, int, int>> events; // x, y1, y2, dif
    rep(i, 0, n){
        cin >> rs[i].f.f >> rs[i].f.s >> rs[i].s.f >> rs[i].s.s;
        rs[i].f.f += 1e6, rs[i].f.s += 1e6, rs[i].s.f += 1e6, rs[i].s.s += 1e6;
        if(rs[i].f > rs[i].s) swap(rs[i].f, rs[i].s);
        events.emplace_back(rs[i].f.f, rs[i].f.s, rs[i].s.s, 1);
        events.emplace_back(rs[i].s.f, rs[i].f.s, rs[i].s.s, -1);
    }
    ll ans = 0;
    sort(all(events));
    int lim = 2e6 + 10;
    Node tree(0, lim);
    rep(i, 0, sz(events) - 1){
        // cout << "got to events " << i << endl;
        auto [x, y1, y2, dif] = events[i];
        auto [x1, _y1, _y2, _dif] = events[i + 1];
        ll dt = x1 - x;
        // cout << "got to events " << i << endl;

        tree.add(y1, y2, dif);
        ll area = lim;
        if(tree.val.f == 0) {
            area -= tree.val.s;
        }
        // cout << "area is now " << area << " val " << tree.val.f << " " << tree.val.s << endl;
        ans += area * dt;
    }
    cout << ans << "\n";
    return 0;
}
