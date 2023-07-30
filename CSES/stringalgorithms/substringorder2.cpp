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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
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
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
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
    string str; cin >> str;
    ll k; cin >> k;
    ll cur = 0;
    SuffixArray sa(str);
	RMQ rmq(sa.lcp);
	vl lengths(sz(sa.sa)), preflengths(sz(sa.sa));
	rep(i, 0, sz(sa.sa)){
		lengths[i] = sz(str) - sa.sa[i];
		preflengths[i] = lengths[i];
		if(i) preflengths[i] += preflengths[i - 1];
	}
	auto lcpquery = [&](int l, int r)->int{
		if(l == r) return lengths[l];
		return rmq.query(l + 1, r + 1);
	};
	int len = 0, l = 1, r = sz(sa.lcp) - 1;
	string ans;
	while(k > 0){
		vpi ranges;
		vl subs;
		int cur = l;
		while(cur <= r){
			int lo = cur, hi = r;
			// find max idx where lcp >= len
			while(lo < hi){
				int mid = lo + (hi - lo + 1) / 2;
				if(lcpquery(cur, mid) >= len + 1){
					lo = mid;
				} else hi = mid - 1;
			}
			ranges.pb({cur, lo});
			ll sum = preflengths[lo];
			if(cur) sum -= preflengths[cur - 1];
			sum -= len * (lo - cur + 1);
			cur = lo + 1;
			subs.pb(sum);
		}
		int idx = -1;
		ll cursum = 0;
		while(idx + 1 < sz(subs)){
			idx++;
			cursum += subs[idx];
			if(cursum >= k) break;
		}
		cursum -= subs[idx];
		k -= cursum;
		ans.pb(str[sa.sa[ranges[idx].f] + len]);
		l = ranges[idx].f;
		r = ranges[idx].s;
		k -= r - l + 1;
		len++;
	}
    cout << ans << nL;
    return 0;
}
