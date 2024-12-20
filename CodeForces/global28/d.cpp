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
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

void solve() {
    int n, m; cin >> n >> m;
    vl a(n), b(m);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, m) cin >> b[i];
    vl c(a);
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    rep(i, 0, m){
        b[i] = lower_bound(all(c), b[i]) - begin(c);
        if(b[i] == sz(c)) b[i] = 0;
    }
    vl cnt(sz(c));
    rep(i, 0, n){
        a[i] = lower_bound(all(c), a[i]) - begin(c);
        cnt[a[i]]++;
    }
    vl suff(cnt);
    for(int i = sz(c)-2; i >= 0; i--) suff[i] += suff[i+1];
    vl ans(m+1);
    sort(all(b));
    vi cont(sz(b));
    rep(i, 0, sz(cont)){
        cont[i] = (b[i] <= a[0] ? 0 : suff[b[i]]);
    }
    sort(all(cont));
    reverse(all(cont));
    RMQ<int> rmq(cont);
    rep(problems, 1, m+1){
        int contests = m / problems;
        int leftover = m % problems;
        ll &res = ans[problems];
        res = contests;
        for(int idx = m-problems, left = contests; idx >= 0 && left; left--, idx -= problems){
            res += rmq.query(idx, idx + problems);
        }
        cout << res << " ";
    }
    cout << "\n";
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
