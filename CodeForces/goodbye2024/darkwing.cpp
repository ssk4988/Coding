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
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		x.push_back(0), sa = lcp = y, iota(all(sa), 0);
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

void solve() {
    string str; cin >> str;
    int n = sz(str);
    SuffixArray sa(str);
    RMQ rmq(sa.lcp);
    vi inv(n+1);
    rep(i, 0, sz(sa.sa)) inv[sa.sa[i]] = i;
    auto lcp = [&](int i, int j) -> int {
        if(inv[i] > inv[j]) swap(i, j);
        return rmq.query(inv[i]+1, inv[j]+1);
    };
    int q; cin >> q;
    vi ans(q);
    vector<vii> qbuckets(n+1);
    rep(i, 0, q){
        int L, R; cin >> L >> R; L--;
        qbuckets[R].pb({L, i});
    }
    set<int> order;
    vector<set<int>> events(n+1);
    auto together = [&](int a, int b) -> int {
        assert(a < b);
        if(inv[a] > inv[b]) return -1;
        int l = lcp(a, b);
        return b + l;
    };
    // x - letter to add
    rep(x, 0, n) {
        order.insert(x);
        if(sz(order) >= 2) {
            int idx = together(*prev(order.find(x)), x);
            if(idx >= x) events[idx].insert(x);
        }
        while(sz(events[x])) {
            int cur = *begin(events[x]);
            events[x].erase(cur);
            auto it = order.lower_bound(cur);
            assert(it != begin(order));
            it = prev(it);
            int prv = *it;
            order.erase(it);
            it = order.lower_bound(cur);
            if(it != begin(order)) {
                it--;
                int prv2 = *it;
                int idx = together(prv2, cur);
                if(idx >= x) events[idx].insert(cur);
            }
        }
        for(auto [l, qid] : qbuckets[x+1]) {
            ans[qid] = *order.lower_bound(l) + 1;
        }
    }
    rep(i, 0, q){
        cout << ans[i] << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    
    return 0;
}

