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

struct UF {
	vi e, sum;
	UF(int n) : e(n, -1), sum(n, 0) {}
    void set(int x, int v){
        sum[x] = v;
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        sum[a] += sum[b];
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vector<string> grid(n);
    vector<array<int, 2>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    rep(i, 0, n){
        cin >> grid[i];
    }
    UF uf(n * m);
    vvi sc(n, vi(m));
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] == '*') continue;
            for(auto [dr, dc] : dir){
                int i1 = i + dr, j1 = j + dc;
                if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                if(grid[i1][j1] == '*') sc[i][j]++;
                uf.set(i * m + j, sc[i][j]);
            }
        }
    }
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] == '*') continue;
            for(auto [dr, dc] : dir){
                int i1 = i + dr, j1 = j + dc;
                if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                if(grid[i1][j1] == '.') uf.join(i * m + j, i1 * m + j1);
            }
        }
    }
    rep(_, 0, k){
        int r, c; cin >> r >> c; r--, c--;
        cout << uf.sum[uf.find(r * m + c)] << "\n";
    }
    
    return 0;
}
