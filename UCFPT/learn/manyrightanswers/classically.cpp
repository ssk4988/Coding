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
const int M = 100;
using bs = bitset<M>;

struct xorbasis {
	vector<bs> basis, made;
	xorbasis() : basis(M), made(M) {}
	bool add(bs x, bs from) {
		rep(i, 0, M) {
			if(basis[i].none()) {
				if(x[i]) {
					basis[i] = x;
					made[i] = from;
					return true;
				}
			} else {
				if(x[i]) {
					x ^= basis[i];
					from ^= made[i];
				}
			}
		}
		return false;
	}
};

vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
void toggle(vector<bs> &grid, int i, int j, int n, int m) {
	grid[i].flip(j);
	rep(k, 0, 4) {
		int i1 = i + dr[k], j1 = j + dc[k];
		if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
		grid[i1].flip(j1);
	}
}

pair<bs, vvi> solve(vector<bs> grid, int n, int m) {
	vvi tog(n, vi(m));
	rep(i, 1, n) {
		rep(j, 0, m) {
			if(grid[i-1][j]) {
				tog[i][j] = 1;
				toggle(grid, i, j, n, m);
			}
		}
	}
	// cerr << "leftover:\n";
	// rep(i, 0, n) {
	// 	rep(j, 0, m) {
	// 		cerr << grid[i][j];
	// 	}
	// 	cerr << "\n";
	// }
	// cerr << "toggles: \n";
	// rep(i, 0, n) {
	// 	rep(j, 0, m) {
	// 		cerr << tog[i][j];
	// 	}
	// 	cerr << "\n";
	// }
	// cerr << "\n";
	return {grid.back(), tog};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<bs> grid(n);
        rep(i, 0, n) {
            string s; cin >> s;
			rep(j, 0, m) {
				grid[i][j] = s[j] == '1';
            }
        }
		auto [cur, _1] = solve(grid, n, m);
		xorbasis xb;
		rep(j, 0, m) {
			toggle(grid, 0, j, n, m);
			auto [res, _2] = solve(grid, n, m);
			res ^= cur;
			toggle(grid, 0, j, n, m);
			bs from;
			from.flip(j);
			xb.add(res, from);
		}
		bs res;
		rep(i, 0, M) {
			if(xb.basis[i].none()) continue;
			if(cur[i]) {
				res ^= xb.made[i];
				cur ^= xb.basis[i];
			}
		}
		if(cur.any()) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		rep(j, 0, m) if(res[j]) toggle(grid, 0, j, n, m);
		auto [last, tog] = solve(grid, n, m);
		assert(last.none());
		rep(j, 0, m) {
			int i = 0;
			if(res[j]) tog[i][j] ^= 1;
		}
		rep(i, 0, n) {
			rep(j, 0, m) {
				cout << "-X"[tog[i][j]];
			}
			cout << "\n";
		}
    }
    
    return 0;
}
