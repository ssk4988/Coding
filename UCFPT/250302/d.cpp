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



const ll mod = 998244353;

vl pw2;

using a4 = array<ll, 4>;
using mat = array<a4, 3>;
struct S {
    int len=0;
    mat m; // {piles, constant from beginning}
    int first = -1, last = -1;
};

S ego(int p = -1) {
    S res;
    if(p == -1) return res;
    res.len = 1;
    rep(i, 0, 3) {
        rep(j, 0, 4) res.m[i][j] = 0;
    }
    res.m[p][p] = 1;
    rep(i, 0, 3) {
        if(i == p) continue;
        int other = 1^2^i^p;
        res.m[i][other] = 1;
        res.m[i][3] = 1;
    }
    res.first = res.last = p;
    return res;
}
S op(S a, S b) {
	if(a.len == 0 || b.len == 0) return a.len == 0 ? b : a;
    S res;
    res.len = a.len + b.len;
    rep(i, 0, 3) {
        rep(j, 0, 4) res.m[i][j] = 0;
    }
    rep(i, 0, 3) {
        res.m[i][3] = b.m[i][3] * pw2[a.len] % mod;
        rep(j, 0, 3) {
            rep(k, 0, 3) {
                (res.m[i][j] += a.m[k][j] * b.m[i][k]) %= mod;
            }
        }
		rep(j, 0, 3) {
			(res.m[i][3] += a.m[j][3] * b.m[i][j]) %= mod;
		}
    }
    res.first = a.first; res.last = b.last;
    return res;
}
using F = int;
F composition(F newer, F older) { return newer; }
S mapping(F f, S s) {
	return s;
}
F id() { return 0; }


struct Tree {
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	Tree(size_t m) {
		n = m; 
		size = 1;
		while(size < m) size *= 2;log = __lg(size);
		d = vector(2*size, ego());
		lz = vector(size, id());
	}
	void update(int k) { d[k] = op(d[2*k], d[2*k + 1]); }
	void fid(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		fid(2 * k, lz[k]);
		fid(2 * k + 1, lz[k]);
		lz[k] = id();
	}
	#define tip for (int i = 1; i <= log; i++)
	#define dip for (int i = log; i >= 1; i--)
	#define check(p) { if (((1<<i)-1) & l) p(l >> i);\
	                   if (((1<<i)-1) & r) p((r-1) >> i); }
	void set(int p, S x) {
		p += size;
		dip push(p >> i);
		d[p] = x;
		tip update(p >> i);
	}
	S prod(int l, int r) {
		l += size; r += size;
		dip check(push);
		S sml = ego(); S smr = ego();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l /= 2, r /= 2;
		}
		return op(sml, smr);
	}
	void apply(int l, int r, F f) {
		l += size; r += size;
		int l2 = l, r2 = r;
		dip check(push);
		while (l < r) {
			if (l & 1) fid(l++, f);
			if (r & 1) fid(--r, f);
			l /= 2, r /= 2;
		}
		l = l2; r = r2;
		tip check(update);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, q; cin >> n >> q;
	pw2.push_back(1);
	rep(i, 0, 2*n) pw2.push_back(pw2.back() * 2 % mod);
	vi pos(n);
	Tree tree(n);
	rep(i, 0, n) {
		cin >> pos[i]; pos[i]--;
		tree.set(i, ego(pos[i]));
	}
	rep(qid, 0, q) {
		char c; cin >> c;
		int l, r; cin >> l >> r;
		l--;
		if(c == 'c') {
			pos[l] = --r;
			tree.set(l, ego(pos[l]));
		} else {
			S res = tree.prod(l, r);
			cout << res.m[0][3] << "\n";
		}
	}


    return 0;
}
