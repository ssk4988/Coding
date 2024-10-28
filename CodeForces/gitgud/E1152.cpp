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

vi eulerWalk(vector<vector<pi>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi b(n-1), c(n-1);
    rep(i,0,n-1) cin >> b[i];
    rep(i,0,n-1) cin >> c[i];
    map<int, int> rl;
    rep(i, 0, n-1){
        if(b[i] > c[i]){
            cout<<"-1\n";
            return 0;
        }
        if(!rl.count(b[i])) rl[b[i]] = sz(rl);
        b[i] = rl[b[i]];
    }
    rep(i, 0, n-1){
        if(!rl.count(c[i])) rl[c[i]] = sz(rl);
        c[i] = rl[c[i]];
    }
    vector<vpi> adj(sz(rl));
    map<int, int> freq;
    rep(i, 0, n-1){
        adj[b[i]].pb({c[i], i});
        adj[c[i]].pb({b[i], i});
        freq[b[i]]++;
        freq[c[i]]++;
    }
    int odd = 0;
    for(auto [key, val] : freq) {if(val & 1) odd = key; }
    // if(odd == -1){
    //     cout << "-1\n";
    //     return 0;
    // }

    vi res = eulerWalk(adj, n-1, odd);
    if(sz(res)==0) cout << "-1\n";
    map<int, int> rd;
    for(auto [k,v] : rl) rd[v] = k;
    for(int i : res) cout << rd[i] << " ";
    cout << "\n";
    return 0;
}
