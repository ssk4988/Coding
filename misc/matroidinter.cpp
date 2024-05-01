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
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct ColorMat {
	vi cnt, clr;
	ColorMat(int n, vector<int> clr) : cnt(n), clr(clr) {}
	bool check(int x) { return !cnt[clr[x]]; }
	void add(int x) { cnt[clr[x]]++; }
	void clear() { fill(all(cnt), 0); }
};
struct GraphMat {
	UF uf;
	vector<array<int, 2>> e;
	GraphMat(int n, vector<array<int, 2>> e) : uf(n), e(e) {}
	bool check(int x) { return !uf.sameSet(e[x][0], e[x][1]); }
	void add(int x) { uf.join(e[x][0], e[x][1]); }
	void clear() { uf = UF(sz(uf.e)); }
};
template <class M1, class M2> struct MatroidIsect {
	int n;
	vector<char> iset;
	M1 m1; M2 m2;
	MatroidIsect(M1 m1, M2 m2, int n) : n(n), iset(n + 1), m1(m1), m2(m2) {}
	vi solve() {
		rep(i,0,n) if (m1.check(i) && m2.check(i))
			iset[i] = true, m1.add(i), m2.add(i);
		while (augment());
		vi ans;
		rep(i,0,n) if (iset[i]) ans.push_back(i);
		return ans;
	}
	bool augment() {
		vector<int> frm(n, -1);
		queue<int> q({n}); // starts at dummy node
		auto fwdE = [&](int a) {
			vi ans;
			m1.clear();
			rep(v, 0, n) if (iset[v] && v != a) m1.add(v);
			rep(b, 0, n) if (!iset[b] && frm[b] == -1 && m1.check(b))
				ans.push_back(b), frm[b] = a;
			return ans;
		};
		auto backE = [&](int b) {
			m2.clear();
			rep(cas, 0, 2) rep(v, 0, n)
				if ((v == b || iset[v]) && (frm[v] == -1) == cas) {
					if (!m2.check(v))
						return cas ? q.push(v), frm[v] = b, v : -1;
					m2.add(v);
				}
			return n;
		};
		while (!q.empty()) {
			int a = q.front(), c; q.pop();
			for (int b : fwdE(a))
				while((c = backE(b)) >= 0) if (c == n) {
					while (b != n) iset[b] ^= 1, b = frm[b];
					return true;
				}
		}
		return false;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
