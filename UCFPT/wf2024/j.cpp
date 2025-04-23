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
const ll inf = 1e15;
using mat = array<array<ll, 5>, 5>;
mat make(bool robot=false, ll w=0, ll dx=0) {
    mat res;
    rep(i, 0, 5){
        rep(j, 0, 5) res[i][j] = -inf;
    }
    if(!robot) {
        res[0][0] = 0;
        res[0][2] = res[0][4] = w;
        res[1][0] = res[1][1] = w-dx;
        res[2][2] = w-dx;
        res[3][0] = res[3][3] = w-2*dx;
        res[4][4] = w-2*dx;
    } else {
        res[0][1] = res[0][0] = 0;
        res[2][0] = res[2][3] = -dx;
        res[4][1] = -2*dx;
    }
    return res;
}
mat operator*(mat a, mat b) {
    mat res;
    rep(i, 0, 5) {
        rep(j, 0, 5) {
            res[i][j] = -inf;
            rep(k, 0, 5) {
                res[i][j] = max(res[i][j], a[i][k]+b[k][j]);
            }
        }
    }
    return res;
}


struct Tree {
    using T = mat;
	T f(T a, T b) { return a*b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n, make()), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = make(), rb = make();
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
    vvi queries;
    vi locs;
    const int right = 1e8+10;
    locs.push_back(right);
    rep(i, 0, n) {
        int t; cin >> t;
        int x; cin >> x;
        locs.push_back(x);
        queries.push_back(vi{x});
        if(t == 2) {
            int c; cin >> c;
            queries.back().push_back(c);
        }
    }
    sort(all(locs));
    locs.erase(unique(all(locs)), end(locs));
    Tree tree(sz(locs));
    rep(i, 1, sz(locs)) {
        ll dx = locs[i]-locs[i-1];
        tree.update(i, make(false, 0, dx));
    }
    rep(i, 0, n) {
        ll x = queries[i][0];
        x = lower_bound(all(locs), x) - begin(locs);
        ll dx = locs[x];
        if(x) dx -= locs[x-1];
        if(sz(queries[i]) >= 2) {
            int c = queries[i][1];
            tree.update(x, make(false, c, dx));
        } else tree.update(x, make(true, 0, dx));
        mat res = tree.query(0, sz(locs));
        cout << res[0][0] << "\n";
    }
    
    
    return 0;
}
