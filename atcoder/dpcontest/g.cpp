#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct T {
    ll sum = 0, pref=0, suff=0, ans=0;
    T(ll v=0) {
        // v = max(v, 0LL);
        // if(v == 0) v--;
        pref = suff = ans = max(v, 0LL);
        sum = v;
    }
};
// T e() {return T(); }
T unit = T();
 
T op(T l, T r) {
    T res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}


// using T = array<array<ll, 3>, 3>;
// using a2 = array<ll, 3>;
// const ll inf = 1e18;
// T make(ll v) {

//     if(v == 0) {
//         return T{a2{0, inf}, a2{inf, 1}};
//     }
//     return T{a2{v, inf}, a2{inf, 0}};
// }

// T unit = T{a2{-1, inf}, a2{inf, 0}};

struct Tree {
	T f(T a, T b) { 
        // if(a[0][0] == -1) return b;
        // if(b[0][0] == -1) return a;
        // T res = T{a2{inf, inf}, a2{inf, inf}};
        // rep(i, 0, 2) {
        //     rep(j, 0, 2) rep(k, 0, 2) rep(l, 0, 2) {

        //         res[i][l] = min(res[i][l], a[i][j] + b[k][l]);
        //     }
        // }
        // return res;
        return op(a, b);
    } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, q; cin >> n >> q;
    Tree tree(n);
    ll tot = 0;
    vl cur(n);
    rep(i, 0, n) {
        ll v; cin >> v;
        cur[i] = v;
        tot += v;
        tree.update(i, T(v == 0 ? -1 : v));
    }
    rep(i, 0, q) {
        int id, v; cin >> id >> v; id--;
        tot -= cur[id];
        cur[id] = v;
        tot += v;
        tree.update(id, T(v == 0 ? -1 : v));
        T res = tree.query(0, n);
        // cerr << tot << " " << res.ans << "\n";
        cout << tot - res.ans << "\n";
    }
    return 0;
}
