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

using S = array<int, 3>;
S op(S a, S b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2]}; }
S ego(int i=-1) { 
    if(i==-1) return {0, 0, 0}; 
    return {1*(i==0), 1*(i==1), 1*(i==2)};
}
using F = int;
F id() { return -1; }
S mapping(F f, S s) {
    if(f == -1) return s;
    int tot = s[0] + s[1] + s[2];
    return {tot * (f==0), tot*(f==1), tot*(f==2)};
}
F composition(F newer, F older) {
	if(newer != -1) return newer;
	return older;
}
struct Tree {
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	Tree(size_t m) {
		n = m; 
        size = 1;
        while(size < m) size *= 2;
        log = __lg(size);
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

const int mod = 998244353;

vi in;
Tree tree(1);

int getpos(S v) {
	if(v[0]) return 0;
	if(v[1]) return 1;
	return 2;
}

// move_disk - get a disk into a certain spot, might need to stackify
// move_one - smallest op, move a disk by itself into spot, assuming it can
// stackify - get all disks <= d onto a certain pile
const int N = 1e5 + 100;
int stack_dp[N][3][3];

int move_one(int d, int from, int to) {
	if(d < 0) return 0;
	assert(abs(from-to) <= 1);
	if(from == to) return 0;
	tree.set(d, ego(to));
	return 1;
}

int stackify(int d, int to) {
    if(d < 0) return 0;
    S cur = tree.prod(0, d+1);
	int from = getpos(tree.prod(d, d+1));
	// cerr << "stackify " << d << " from " << from << " to " << to << endl;
	int anstmp = 0;
	bool isdp = false;
    if(cur[from] != d+1) {
        // not one stack
    } else {
		isdp = true;
        if(stack_dp[d][from][to] != -1) {
            tree.apply(0, d+1, to);
            return stack_dp[d][from][to];
        }
    }
	int original_from = from;
	if(from == to) {
		if(isdp) {
			stack_dp[d][from][to] = anstmp;
		} else {
			(anstmp += stackify(d-1, to)) %= mod;
		}
		tree.apply(0, d+1, to);
		return anstmp;
	}
	int dv = from < to ? 1 : -1;
	while(from != to) {
		int from1 = from + dv;
		int other = 3-from-from1;
		(anstmp += stackify(d-1, other)) %= mod;
		(anstmp += move_one(d, from, from1)) %= mod;
		from = from1;
	}
	(anstmp += stackify(d-1, to)) %= mod;
	if(isdp) {
		// cerr << "stackdp: " << d << " from " << original_from << " to " << to << " = " << anstmp << endl;
		stack_dp[d][original_from][to] = anstmp;
	}
	tree.apply(0, d+1, to);
	return anstmp;
}

int move_disk(int d, int to) {
	int from = getpos(tree.prod(d, d+1));
	if(from == to) {
		return 0;
	}
	int anstmp = 0;
	int dv = from < to ? 1 : -1;
	while(from != to) {
		int from1 = from + dv;
		int other = 3-from-from1;
		(anstmp += stackify(d-1, other)) %= mod;
		(anstmp += move_one(d, from, from1)) %= mod;
		from = from1;
	}
	return anstmp;
}

void solve() {
    int n; cin >> n;
    in = vi(n);
    tree = Tree(n);
	rep(i, 0, n) {
		rep(j, 0, 3) {
			rep(k, 0, 3) {
				stack_dp[i][j][k] = -1;
			}
		}
	}
    rep(i, 0, n) {
        cin >> in[i]; in[i]--;
        tree.set(i, ego(in[i]));
    }
	vi last(n);
	rep(i, 0, n) {
		cin >> last[i]; last[i]--;
	}
	int ans = 0;
	for(int i = n-1; i >= 0; i--) {
		(ans += move_disk(i, last[i])) %= mod;
	}
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
