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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0;
    pii val;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = max(l->val, r->val);
		}
		else val = {0, lo};
	}
	pii query(int L, int R) {
		if (R <= lo || hi <= L) return {-inf, -1};
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) val = {x, lo}, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val.f += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        Node tree(0, n);
        vi dfsorder, time(n), subsz(n, 1), par(n, -1), paredge(n, 1), depth(n);
        paredge[0] = 0;
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            par[u] = p;
            time[u] = sz(dfsorder);
            dfsorder.pb(u);
            tree.set(time[u], time[u]+1, depth[u]);
            for(int v : adj[u]){
                if(v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        vi ans(2*n);
        int curans = 0;
        // rep(i, 0, n) cout << dfsorder[i] << " ";
        // cout << "\n";
        // rep(i, 0, n) cout << depth[i] << " ";
        // cout << "\n";
        rep(i, 0, n){
            auto [score, best] = tree.val;
            best = dfsorder[best];
            // cout << score << " " << best << "\n";
            curans += score;
            int cur = best;
            tree.add(time[cur], time[cur]+1, -5);
            while(paredge[cur]) {
                tree.add(time[cur], time[cur] + subsz[cur], -1);
                paredge[cur] = false;
                cur = par[cur];
            }
            ans[(i+1)/2] = n-1 - curans;
        }
        rep(i, 0, n-1) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
