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

// x = (x' + y') / 2
// y = y' - x

pi getorig(pi augment){
    return {(augment.f + augment.s) / 2, augment.s - (augment.f + augment.s) / 2};
}

pi augment(pi orig){
    return {orig.f - orig.s, orig.f + orig.s};
}

const pi inf = {1e9, 1e9};
// const pi auginf = augment(inf);
pi comb(pi a, pi b){
    return min(a, b);
}
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    pi val = inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = comb(l->val, r->val);
		}
	}
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		return comb(l->query(L, R), r->query(L, R));
	}
	void set(int idx, pi x) {
		if (idx+1 <= lo || hi <= idx) return;
		if (idx <= lo && hi <= idx+1) {
            // cout << "set val " << x.f << " " << x.s << " in seg " << lo << " " << hi << "\n"; 
            val = x;
        }
		else {
			l->set(idx, x), r->set(idx, x);
			val = comb(l->val, r->val);
		}
	}
};


struct Node2 {
	Node2 *l = 0, *r = 0;
	int lo, hi;
    Node *val;
	Node2(int lo, int hi, int lo1, int hi1) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node2(lo, mid, lo1, hi1); r = new Node2(mid, hi, lo1, hi1);
		}
        val = new Node(lo1, hi1);
	}
	pi query(int L, int R, int L1, int R1) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val->query(L1, R1);
		return comb(l->query(L, R, L1, R1), r->query(L, R, L1, R1));
	}
	void set(int idx, int idx1, pi x) {
		if (idx+1 <= lo || hi <= idx) return;
        // cout << "in 2nd layer " << lo << "," << hi << "\n";
		if (idx <= lo && hi <= idx+1) {
            val->set(idx1, x);
            return;
        }
		else {
			l->set(idx, idx1, x), r->set(idx, idx1, x);
            val->set(idx1, comb(l->query(lo, hi, idx1, idx1+1), r->query(lo, hi, idx1, idx1+1)));
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    pi c1 = {0, 0}, c2 = {n, 0}, c3 = {n, m}, c4 = {0, m};
    pi oc1 = augment(c1), oc2 = augment(c2), oc3 = augment(c3), oc4 = augment(c4);
    int minr = min({oc1.f, oc2.f, oc3.f, oc4.f}), maxr = max({oc1.f, oc2.f, oc3.f, oc4.f});
    int minc = min({oc1.s, oc2.s, oc3.s, oc4.s}), maxc = max({oc1.s, oc2.s, oc3.s, oc4.s});
    // cout << minr << " " << maxr << " " << minc << " " << maxc << "\n";
    Node2 tree(minr, maxr, minc, maxc);
    rep(i, 0, n){
        rep(j, 0, m){
            auto [r, c] = augment({i, j});
            // cout << "add " << i << "," << j << " at " << r << "," << c << "\n";
            tree.set(r, c, {i, j});
            auto [r1, c1] = tree.query(r, r+1, c, c+1);
            // cout << "at: " << r1 << " " << c1 << "\n";
        }
    }
    rep(_, 0, k){
        int i, j; cin >> i >> j; i--, j--;
        auto [r, c] = augment({i, j});
        int d = -1, lim = 2005;
        for(int dif = 1 << 12; dif; dif /= 2){
            auto [r1, c1] = tree.query(r - (d + dif), r + (d + dif) + 1, c - (d + dif), c + (d + dif) + 1);
            if(pi{r1, c1} == inf){
                d += dif;
            }
        }
        d++;
        // cout << "radius is " << d << "query range: " << (r-d) << " to " << (r+d+1) << " " << (c-d) << " to " << (c+d+1) << "\n";
        auto [r1, c1] = tree.query(r - d, r + d + 1, c - d, c + d + 1);
        // auto [i1, j1] = getorig({r1, c1});
        cout << (r1 + 1) << " " << (c1 + 1) << "\n";
        // cout << "before:\n";
        auto [r3, c3] = tree.query(minr, maxr, minc, maxc);
        // cout << "left: " << (r3+1) << " " << (c3+1) << "\n";
        auto [r2, c2] = augment({r1, c1});
        tree.set(r2, c2, inf);
        // cout << "after:\n";
        tie(r1, c1) = tree.query(minr, maxr, minc, maxc);
        // cout << "left: " << (r1+1) << " " << (c1+1) << "\n";
        r = 3, c = 0;
        tie(r, c) = augment({r, c});
        tie(r1, c1) = tree.query(r, r+1, c, c+1);
        // cout << "4,1: " << (r1+1) << " " << (c1+1) << "\n";
    }

    // cout << augment({3, 0}).f << " " << augment({3, 0}).s << "\n";
    // cout << augment({3, 1}).f << " " << augment({3, 1}).s << "\n";

    return 0;
}