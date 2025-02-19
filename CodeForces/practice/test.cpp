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

vi tin, st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int u, int par, F& f) {
	int me = tin[u] = ++Time, low = me;
	for (auto [v, e] : ed[u]) if (e != par) {
		if (tin[v]) {
			low = min(low, tin[v]);
			if (tin[v] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(v, e, f);
			low = min(low, up);
			if (up >= me) { // e is a bridge if up > me
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else st.push_back(e);
		}
	}
	return low;
}

template<class F>
void bicomps(F f) {
	tin.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!tin[i]) dfs(i, -1, f);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
