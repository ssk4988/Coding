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

struct TreeMN {
	typedef int T;
	static constexpr T unit = INT_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	TreeMN(int n = 0, T def = unit) : s(2*n, def), n(n) {}
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

struct TreeMX {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	TreeMX(int n = 0, T def = unit) : s(2*n, def), n(n) {}
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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        vi par(n);
        par[0] = -1;
        vvi child(n);
        rep(i, 1, n){
            cin >> par[i]; par[i]--;
            child[par[i]].pb(i);
        }
        vi perm(n), inv(n);
        vector<set<int>> childset(n);
        rep(i, 0 ,n){
            cin >> perm[i]; perm[i]--;
            inv[perm[i]] = i;
            for(int v : child[i]) childset[i].insert(v);
        }
        vi depth(n), subsz(n, 1), fastpar(n, -1); // lowest parent with 2+ child
        vi tin(n);
        int T = 0;
        auto dfs = [&](int u, auto &&dfs) ->void {
            tin[u] = T++;
            if(par[u] != -1 && sz(child[par[u]]) < 2){
                fastpar[u] = fastpar[par[u]];
            } else fastpar[u] = par[u];
            for(int v : child[u]){
                depth[v] = 1 + depth[u];
                dfs(v, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, dfs);
        TreeMN mnt(n);
        TreeMX mxt(n);
        rep(i, 0, n){
            mnt.update(tin[i], inv[i]);
            mxt.update(tin[i], inv[i]);
        }
        vi plus1(n); // num nodes who have child after in perm
        int plus1cnt = 0;
        int plus1target = 0;
        auto check = [&](int u){
            if(sz(child[u]) == 0) return;
            plus1cnt -= plus1[u];
            plus1[u] = 0;
            if (inv[u] + 1 < n && childset[u].count(perm[inv[u]+1])) plus1[u] = 1;
            plus1cnt += plus1[u];
        };
        rep(i, 0, n){
            if(sz(child[i]) > 0) plus1target++;
            check(i);
        }
        vi good(n);
        int goodcnt = 0;
        auto calc = [&](int u, auto &&calc) -> void {
            if (sz(child[u]) < 2) {
                u = fastpar[u];
            }
            for(; u != -1; u = fastpar[u]) {
                goodcnt -= good[u];
                int mn = mnt.query(tin[u], tin[u] + subsz[u]);
                int mx = mxt.query(tin[u], tin[u] + subsz[u]);
                good[u] = mn == inv[u] && mx == inv[u] + subsz[u] - 1;
                goodcnt += good[u];
            }
        };
        int goodtarget = 0;
        rep(i, 0, n){
            goodtarget += sz(child[i]) >= 2;
            if(sz(child[i]) >= 2){
                int mn = mnt.query(tin[i], tin[i] + subsz[i]);
                int mx = mxt.query(tin[i], tin[i] + subsz[i]);
                good[i] = mn == inv[i] && mx == inv[i] + subsz[i] - 1;
                goodcnt += good[i];
            }
        }
        rep(i, 0, q){
            int x, y; cin >> x >> y; x--, y--;
            swap(perm[x], perm[y]);
            swap(inv[perm[x]], inv[perm[y]]);
            for(int v : {x, y}){
                mnt.update(tin[perm[v]], inv[perm[v]]);
                mxt.update(tin[perm[v]], inv[perm[v]]);
                check(perm[v]);
                if(par[perm[v]] != -1) check(par[perm[v]]);
                calc(perm[v], calc);
            }
            cout << (goodcnt == goodtarget && plus1cnt == plus1target ? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}
