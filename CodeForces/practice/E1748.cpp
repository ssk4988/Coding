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
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vpi a(n);
        rep(i, 0, n){
            cin >> a[i].f;
            a[i].s = -i;
        }
        RMQ<pi> rmq(a);
        auto dfs = [&](int l, int r, auto &&dfs) -> vl {
            if(l >= r) return vl(m + 1, 1);
            auto p = rmq.query(l, r);
            int mid = -p.s;
            if(l + 1 == r){
                vl res(m + 1);
                iota(all(res), 0);
                return res;
            }
            vl lef = dfs(l, mid, dfs), rig = dfs(mid+1, r, dfs);
            vl res(m + 1);
            rep(i, 1, m+1) res[i] = mod(lef[i-1] * rig[i] + res[i-1]);
            return res;
        };
        vl ans = dfs(0, n, dfs);
        cout << ans.back() << "\n";
    }
    
    return 0;
}
