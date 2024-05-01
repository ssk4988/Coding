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
 
template<class T, int... Ns> struct BIT {
	T val = 0;
	void update(T v) { val += v; }
	T query() { return val; }
};
template<class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	// BIT<T, Ns...> bit[N + 1];
	map<int, BIT<T, Ns...>> bit; // if the mem use is too high
	template<class... Args> void update(int i, Args... args) {
		for (i++; i <= N; i += i & -i) bit[i].update(args...);
	}
	template<class... Args> T query(int i, Args... args) {
		T ans = 0;
		for (i++; i; i -= i & -i) ans += bit[i].query(args...);
		return ans;
	}
	template<class... Args,
		enable_if_t<(sizeof...(Args) == 2 * sizeof...(Ns))>* =
			nullptr>
	T query(int l, int r, Args... args) {
		return query(r, args...) - query(l - 1, args...);
	}
};
 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    BIT<int, 1000, 1000> bit;
    vvi grid(n, vi(n));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n){
            grid[i][j] = str[j] == '*' ? 1 : 0;
        }
    }
    auto upd = [&](int x, int y, int a) {
        bit.update(x, y, a);
    };
    auto qry = [&](int x, int y) {
        return bit.query(x, y);
    };
    rep(i, 0, n){
        rep(j, 0, n){
            if(grid[i][j]) upd(i, j, grid[i][j]);
        }
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int x, y; cin >> x >> y; x--, y--;
            upd(x, y, grid[x][y] > 0 ? -1 : 1);
            grid[x][y] = !grid[x][y];
        }
        else{
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            x1--,y1--,x2--,y2--;
            // cout << x1 << " " << y1 << " " << x2 << " " << y2 << nL;
            ll ans = qry(x2, y2);
            ans -= qry(x1 - 1, y2);
            ans -= qry(x2, y1 - 1);
            ans += qry(x1 - 1, y1 - 1);
            cout << ans << nL;
        }
    }
    
    return 0;
}
