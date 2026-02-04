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

/*
always hit smallest in range
recurse on subranges

5 2 7
3 0 5 +2
+8

5 2 7
3 0 5 +1
+5
5 2 7
2 -1 4 +1
+3

5 2 7
1 -1 3 +1
+26

state:
l,r range, how many hits already done

5 4 1 3 2

x x 5 9 7
8 5 9 7
1: 29
2: 3+1+2=6    1p 2, -1, 3, 1 2p
3: 3+1+1=5    1p 2, -1, 3, 1 
4: 2+1=3      1p 0, -3, 1, -1
given a-b edge, find extra accumulation on k that b provides that a doesn't
7-9:
ceil[b/k]-ceil[a/k]
ceil(a / b) = (a-1) / b + 1
*/

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
vii gen(int x) {
    vii ans;
    for (int l = 1, r; l <= x && (r = x / (x / l)); l = r + 1) ans.push_back({l, r+1});
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    int mx = *max_element(all(a));
    vl pref(mx+10);
    vii b(n);
    rep(i, 0, n) b[i] = {a[i], i};
    RMQ rmq(b);
    vi par(n);
    auto dfs = [&](int l, int r, auto &&dfs) -> int {
        if(l == r) return -1;
        auto [v, i] = rmq.query(l, r);
        // cerr << l << " i=" << i << " " << r << endl;
        int j = dfs(i+1, r, dfs);
        if(j != -1) par[j] = a[i];
        j = dfs(l, i, dfs);
        if(j != -1) par[j] = a[i];
        return i;
    };
    dfs(0, n, dfs);
    rep(i, 0, n) {
        int x = par[i];
        int y = a[i];
        // cerr << i << " " << x << " " << y << endl;
        vii rng = gen(x-1);
        if(x != 0) {

            rng.push_back({x, mx+1});
            rep(j, 0, sz(rng)) {
                auto [l, r] = rng[j];
                // cerr << "range " << l << " to " << r << endl;
                int cont = (x-1)/l+1;
                // cerr << "sub " << cont << " range " << l << " to " << r << endl;
                pref[min(mx+1, l)] -= (cont);
                pref[min(mx+1, r)] += cont;
            }
        }
        rng = gen(y-1);
        rng.push_back({y, mx+1});
        rep(j, 0, sz(rng)) {
            auto [l, r] = rng[j];
            // cerr << "range " << l << " to " << r << endl;

            int cont = (y-1)/l+1;
            // cerr << "add " << cont << " range " << l << " to " << r << endl;

            pref[min(mx+1, l)] += (cont);
            pref[min(mx+1, r)] -= cont;
        }
    }
    rep(i, 1, mx+1) {
        pref[i] += pref[i-1];
        cout << pref[i] << " ";
    }
    cout << "\n";
    
    
    return 0;
}
