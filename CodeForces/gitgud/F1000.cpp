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

struct Tree {
	typedef pi T;
	static constexpr T unit = pi{INT_MAX, -1};
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
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
    int n; cin >> n;
    vi a(n);
    Tree tree(n);
    rep(i, 0, n){
        cin >> a[i]; a[i]--;
    }
    const int N = 5e5 + 10;
    vi last(N, -1);
    vi left(n), right(n);
    rep(i, 0, n){
        left[i] = last[a[i]]+1;
        last[a[i]] = i;
    }
    last = vi(N, n);
    for(int i = n- 1; i >= 0; i--){
        right[i] = last[a[i]]-1;
        last[a[i]] = i;
    }
    int q; cin >> q;
    vpi qs(q);
    vvi qints(n);
    vi ans(q, -1);
    rep(i, 0, q){
        cin >> qs[i].f >> qs[i].s; qs[i].f--, qs[i].s--;
        qints[qs[i].s].pb(i);
    }
    rep(i, 0, n){
        tree.update(i, {left[i], a[i]});
        if(left[i] > 0){
            tree.update(left[i]-1, tree.unit);
        }
        for(int j : qints[i]){
            auto [l, r] = qs[j];
            pi best = tree.query(l, r+1);
            // cout << j << " " << l << " " << r << " " << best.f << " " << best.s << endl;
            if(best.f <= l) ans[j] = best.s;
        }
    }
    rep(i, 0, q){
        cout << (ans[i]+1) << "\n";
    }

    
    return 0;
}
