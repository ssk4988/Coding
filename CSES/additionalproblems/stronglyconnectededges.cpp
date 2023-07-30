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

vi num, st;
vector<vector<pi>> ed;
int Time;
bool hasbridge = false;
int comps = 0;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, e, y, top = me;
	for (auto pa : ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ hasbridge = true; }
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]){ dfs(i, -1, f); comps++;}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    ed.resize(n);
    vector<unordered_set<int>> adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        ed[a].pb({b, i});
        ed[b].pb({a, i});
        adj[a].insert(b);
        adj[b].insert(a);
    }
    bicomps([](vi val)->void{});
    if(hasbridge || comps > 1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    auto dfs = [&](int cur, auto &&dfs)->void{
        while(adj[cur].size()){
            auto it = adj[cur].begin();
            int nex = *it;
            adj[cur].erase(it);
            adj[nex].erase(cur);
            cout << (cur + 1) << " " << (nex + 1) << nL;
            dfs(nex, dfs);
        }
    };
    dfs(0, dfs);
    
    return 0;
}