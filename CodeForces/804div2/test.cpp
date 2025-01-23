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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
    RMQ() {}
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

template<class T>
RMQ<T> merge(RMQ<T> &a, RMQ<T> &b){
    vector res(a.jmp[0]);
    for(int i = 0; i < b.jmp[0].size(); i++) res[i] = max(res[i], b.jmp[0][i]);
    return res;
}

template<class T>
struct RMQ2D {
	vector<vector<RMQ<T>>> jmp;
	RMQ2D(const vector<RMQ<T>>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = merge(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b, int c, int d) {
		assert(a < b && c < d); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a].query(c, d), jmp[dep][b - (1 << dep)].query(c, d));
	}
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vvi grid{
        {1, 0, 2, 4},
        {2, 1, 3, 2},
        {4, 4, 3, 4},
        {5, 4, 1, 3}
    };
    vector<RMQ<int>> rows;
    for(auto &v : grid) rows.pb(v);
    RMQ2D rmq(rows);
    int q; cin >> q;
    rep(i, 0, q){
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << rmq.query(a, b, c, d) << endl;
    }
    
    return 0;
}
