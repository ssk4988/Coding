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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    vpi v(n);
    rep(i, 0, n-1){
        cin >> a[i];
        a[i]--;
        v[i] = {a[i], i};
    }
    a[n-1] = n-1;
    v[n-1] = {n-1, n-1};
    RMQ<pi> rmq(v);
    vl ans(n);
    ll val = 0;
    for(int i = n-2; i >= 0; i--){
        pi nex = rmq.query(i+1, a[i] + 1);
        ans[i] = n - 1 - a[i] + ans[nex.s] + nex.s - i;
        val += ans[i];
        // cout << i << " " << ans[i] << " " << nex.f << " " << nex.s << " " << ans[nex.s] << endl;
    }
    cout << val << "\n";

    
    return 0;
}
