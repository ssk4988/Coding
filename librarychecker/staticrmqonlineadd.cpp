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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	int l, r;
	RMQ(const vector<T>& V, int l, int r) : jmp(1, V), l(l), r(r) {
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
	RMQ operator+(RMQ &b) {
		vector<T> con(jmp[0]);
		con.insert(con.end(), all(b.jmp[0]));
		return RMQ(con, l, b.r);
	}
};

struct RMQS {
	vector<RMQ<int>> rmqs;
	int added = 0;
	void add(int x) {
		rmqs.emplace_back(vi(1, x), added, added+1);
		added++;
		while(sz(rmqs) >= 2 && sz(rmqs.back().jmp[0]) == sz(rmqs[sz(rmqs)-2].jmp[0])) {
			auto res = rmqs[sz(rmqs)-2] + rmqs.back();
			rmqs.pop_back(); rmqs.pop_back();
			rmqs.push_back(res);
		}
	}
	int query(int l, int r) {
		int ans = INT_MAX;
		for(auto &rmq : rmqs) {
			if(l >= rmq.r || r <= rmq.l) continue;
			ans = min(ans, rmq.query(max(rmq.l, l) - rmq.l, min(rmq.r, r) - rmq.l));
		}
		return ans;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q; 
    vi a(n);
    rep(i,0,n){
        cin >> a[i];
    }
	vi ans(q);
	RMQS rmq;
	vector<vpi> queries(n+1);
    rep(i, 0, q){
        int l, r; cin >> l >> r;
		queries[r].push_back({l, i});
        // cout << t.query(l, r).v << "\n";
    }
	rep(r, 1, n+1){
		rmq.add(a[r-1]);
		for(auto [l, idx] : queries[r]) {
			ans[idx] = rmq.query(l, r);
		}
	}
	rep(i, 0, q) cout << ans[i] << "\n";

    
    
    return 0;
}
