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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(vi s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

struct wt {
	int lo, hi;
	wt *l, *r;
	vi b;             //one indexed V
	//nos are in range [x,y], array indices are [from, to)
	wt (vi::iterator from, vi::iterator to, int lo, int hi) : lo(lo), hi(hi) {
		if(lo == hi or from >= to) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int x){ return x <= mid; };
		b.reserve(to-from+1); b.push_back(0);
		for(auto it = from; it != to; it++)
			b.push_back(b.back() + f(*it));
		auto pivot = stable_partition(from, to, f);
		l = new wt(from, pivot, lo, mid);
		r = new wt(pivot, to, mid+1, hi);
	}
 
	//kth smallest element in [l, r], 1 indexed
	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = b[l-1], rb = b[r], inLeft = b[r] - b[l-1];
		if(k <= inLeft) return this->l->kth(lb+1, rb , k);
		return this->r->kth(l-lb, r-rb, k-inLeft);
	}
 
	//count of nos in [l, r] Less than or equal to k,1 indexed
	int LTE(int l, int r, int k) {
		if(l > r or k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi total, from;
    vector<basic_string<int>> ws(n);
    int sep = 2e5+1;
    rep(i, 0, n) {
        string s; cin >> s;
        for(char c : s) {
            total.pb(c-'a'+1);
            ws[i] += total.back();
            from.pb(i);
        }
        total.pb(sep);
        from.pb(sep++);
    }
    SuffixArray sa(total, sep+5);
    RMQ rmq(sa.lcp);
    vi at(n, -1);
    vi a;
    rep(i, 0, sz(sa.sa)) {
        int j = sa.sa[i];
        if(j == sz(total)) {
            a.pb(sep++);
        } else {
            a.pb(from[j]);
            if(from[j] < n && (at[from[j]] == -1 || sa.sa[at[from[j]]] > j)) at[from[j]] = i;
        }
    }
    basic_string<int> tot(all(total));
    vi ls(n), rs(n);
    rep(i, 0, n) {
        int l = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            if(l+dif < at[i]){
                int lcp = rmq.query(l+dif+1, at[i]+1);
                if(lcp < sz(ws[i])) l += dif;
            }
        }
        l++;
        int r = at[i]+1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            if(r+dif <= sz(sa.sa)){
                int lcp = rmq.query(at[i]+1, r+dif);
                if(lcp >= sz(ws[i])) r += dif;
            }
        }
        ls[i] = l, rs[i] = r;
    }
    wt wave(all(a), 0, sep);
    // WaveletTree wt(a, sep);
    rep(qid, 0, q) {
        int l, r, k; cin >> l >> r >> k; k--; l--;
        ll ans = wave.LTE(ls[k]+1, rs[k], r-1);
        if(l) ans -= wave.LTE(ls[k]+1, rs[k], l-1);
        // ll ans = wt.count(ls[k], rs[k], r) - wt.count(ls[k], rs[k], l);
        cout << ans << "\n";
    }
    
    return 0;
}
