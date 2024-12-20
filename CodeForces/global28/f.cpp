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
    int n; cin >> n;
    vl a(n), b(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vll b2(n);
    rep(i, 0, n){
        cin >> b[i];
        b2[i] = {b[i], i};
    }
    RMQ rmq(b2);
    const ll inf = 1e18+20;
    const int B = 65;
    auto dfs = [&](int l, int r, auto &&dfs) -> vl {
        auto [mnv, mni] = rmq.query(l, r);
        vl left(B, 1), right(B, 1);
        if(mni > l){
            left = dfs(l, mni, dfs);
        }
        if (mni+1 < r) right = dfs(mni+1, r, dfs);
        vl ans(B, inf);
        rep(use, 0, B){
            ll res = inf;
            rep(luse, 0, use+1){
                res = min(res, max(left[luse], right[use - luse]));
            }
            res = max(res, a[mni]);
            ans[use] = res;
        }
        rep(use, 1, B){
            ans[use] = min(ans[use], (ans[use-1]-1) / mnv + 1);
        }
        return ans;
    };
    vl res = dfs(0, n, dfs);
    ll ans = inf;
    rep(i, 0, sz(res)) if(res[i] == 1){
        ans = i;
        break;
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
