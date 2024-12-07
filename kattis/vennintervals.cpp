#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int k; cin >> k;
	map<string, int> rl;
	map<int, string> lr;
	vvi rng;
	rep(i, 0, k){
		int n; cin >> n;
		rng.pb({});
		rep(j, 0, n){
			string s; cin >> s;
			if(!rl.count(s)){
				rl[s] = sz(rl);
				lr[rl[s]] = s;
			}
			rng.back().pb(rl[s]);
		}
	}
	int n = sz(rl);
	vvi adj(n);
	rep(i, 0, k){
		for(int j : rng[i]){
			adj[j].pb(i);
		}
	}
	vi use(n), userng(k);
	vi ls(n, -1), rs(n, -1);
	int t = 0;
	rep(i, 0, n){
		sort(all(adj[i]), [&](int a, int b) { return sz(rng[a]) < sz(rng[b]); });
	}
	auto badsol = [](){
		cout << "IMPOSSIBLE\n";
		return 0;
	};
	vi sources;
	rep(i, 0, n){
		if(sz(adj[i]) == 1){
			sources.pb(i);
			continue;
		}
		int cnt2 = 0, cnt1 = 0;
		for(int v : adj[i]){
			if(sz(rng[v]) == 2) cnt2++;
			if(sz(rng[v]) == 1) cnt1++;
		}
		if(cnt2 == 1 && cnt1 == 1) sources.pb(i);
	}
	for(int i : sources){
		if(use[i]) continue;
		queue<int> q;
		q.push(i);
		ls[i] = t;
		use[i] = true;
		while(sz(q)){
			int u = q.front(); q.pop();
			rep(j, 0, sz(adj[u])){
				if(userng[adj[u][j]]) continue;
				for(int v : rng[adj[u][j]]) {
					if(use[v]) continue;
					use[v] = true;
					q.push(v);
					ls[v] = t;
				}
				t++;
				userng[adj[u][j]] = true;
			}
			rs[u] = t;
		}
	}
	rep(i, 0, n){
		if(ls[i] == -1 || rs[i] == -1 || !use[i]) return badsol();
	}
	vvi rng2;
	rep(t1, 0, t) {
		rng2.pb({});
		rep(i, 0, n){
			if(ls[i] <= t1 && t1+1 <= rs[i]) rng2.back().pb(i);
		}
		sort(all(rng2.back()));
	}
	sort(all(rng2));
	rep(i, 0, sz(rng)){
		sort(all(rng[i]));
	}
	sort(all(rng));
	if(rng != rng2) return badsol();
	rep(i, 0, n){
		rep(j, 0, n){
			if(i == j) continue;
			if(ls[i] <= ls[j] && rs[j] <= rs[i]) return badsol();
		}
	}
	rep(i, 0, n){
		cout << lr[i] << " " << ls[i] << " " << rs[i] << "\n";
	}
	
	return 0;
}
