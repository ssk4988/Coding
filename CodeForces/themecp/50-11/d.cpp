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
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    ll base = 0;
    vii ai(n);
    rep(i, 0, n) {
        ai[i] = {a[i], i};
    }
    RMQ rmq(ai);
    vl ans(n);
    // return idx, lsub, rsub
    auto getbase = [&](int l, int r, ll psum, auto &&getbase) -> tuple<ll, vector<array<ll, 3>>, vector<array<ll, 3>>> {
        ll subsz = r-l;
        if(r-l == 0) return {-1, {}, {}};
        auto [mn, u] = rmq.query(l, r);
        // cerr << "on " << l << " to " << r << " min is " << u << "," << mn << "\n";
        // if(r-l == 1) {
        //     base += mn;
        //     return {u, 0, 0};
        // }
        ll lsub = u-l;
        ll rsub = r-(u+1);
        auto [lid, llsub, lrsub] = getbase(l, u, psum + mn * (1 + rsub), getbase);
        auto [rid, rlsub, rrsub] = getbase(u+1, r, psum + mn * (1 + lsub), getbase);
        base += mn * (1+lsub) * (1+rsub);
        ans[u] = -psum;
        ans[u] -= mn * (1+lsub) * (1+rsub);
        vector<array<ll, 4>> mg;
        for(auto [a, b, c] : lrsub) {
            mg.push_back({a, b, c, 0});
        }
        for(auto [a, b, c] : rlsub) {
            mg.push_back({a, b, c, 1});
        }
        sort(all(mg));
        vl sm(2);
        int prv = -1;
        for(auto [a, b, c, t] : mg) {
            if(prv != t){
                ans[u] += c * sm[1-t];
                sm[1-t] = 0;
            }
            prv = t;
            sm[t] += b;
        }
        // sm = vl(2);
        // reverse(all(mg));
        // for(auto [a, b, c, t] : mg) {
        //     ans[u] += sm[1-t] * a;
        //     sm[t] = c;
        // }
        // if(lid != -1 && rid != -1) {
        //     if(a[lid] < a[rid]) {
        //         ans[u] += a[lid] * (1 + llsub) * rsub;
        //     } else {
        //         ans[u] += a[rid] * (1 + rrsub) * lsub;
        //     }
        // }
        llsub.pb({mn, mn * (1 + rsub), subsz});
        rrsub.pb({mn, mn * (1 + lsub), subsz});
        return {u, move(llsub), move(rrsub)};
    };
    getbase(0, n, 0, getbase);
    rep(u, 0, n){
        ans[u] += base;
    }
    // cerr << "Base: " << base << "\n";
    rep(u, 0, n){
        cout << ans[u] << " ";
    }
    cout << "\n";
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
