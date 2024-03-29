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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0, val = inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = min(l->val, r->val);
		}
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int idx, int x) {
		if (idx+1 <= lo || hi <= idx) return;
		if (idx <= lo && hi <= idx+1) val = x, madd = 0;
		else {
			push(), l->set(idx, x), r->set(idx, x);
			val = min(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
    void print() {
        if(lo + 1 == hi){
            cout << val << " ";
            return;
        }
        push();
        l->print(), r->print();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, l; ll s;
    cin >> n >> l >> s;
    vl w(n);
    rep(i, 0, n) cin >> w[i];
    vi par(n);
    vvi child(n);
    rep(i, 1, n){ cin >> par[i]; par[i]--; child[par[i]].pb(i); }
    rep(i, 0, n){
        if(w[i] > s){
            cout << "-1\n";
            return 0;
        }
    }
    vi dep(n), subsz(n, 1);
    vvi bucket(n+1);
    vl pathroot(w);
    vi tour;
    vi time(n);
    vi fakes;
    auto dfs = [&](int u, auto &&dfs) -> void {
        bucket[dep[u]].pb(u);
        time[u] = sz(tour);
        tour.pb(u);
        for(int v : child[u]){
            dep[v] = dep[u] + 1;
            pathroot[v] = pathroot[u] + 1;
            dfs(v, dfs);
            subsz[u] += subsz[v];
        }
    };
    dfs(0, dfs);
    vvi jmp(20, vi(n));
    jmp[0] = par;
    rep(i, 1, sz(jmp)){
        rep(j, 0, n){
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];
        }
    }
    vvi rem(n+1);
    rep(i, 0, n){
        int cur = i;
        if(dep[i] + 1 <= l && pathroot[i] <= s) continue; // is beyond the node
        for(int j = sz(jmp) - 1; j >= 0; j--){
            if(dep[i] - dep[jmp[j][cur]] <= l && pathroot[i] - pathroot[jmp[j][cur]] <= s){
                cur = jmp[j][cur];
            }
        }
        rem[dep[cur]].pb(i);
    }
    Node tree(0, n);
    vi dp(n);
    for(int i = sz(bucket) - 1; i >= 0; i--){
        for(int j : rem[i]){
            tree.set(time[j], inf);
        }
        for(int j : bucket[i]){
            int sum = 1;
            for(int k : child[j]){
                sum += dp[k];
            }
            dp[j] = min(sum, 1 + tree.query(time[j], time[j] + subsz[j]));
            int val = -dp[j];
            for(int k : child[j]){
                val += dp[k];
            }
            tree.add(time[j], time[j] + subsz[j], val);
            tree.set(time[j], dp[j]);
            // cout << j << endl;
            // tree.print();
            // cout << endl;
            // cout << "";
        }

    }
    if(dp[0] >= inf) dp[0] = -1;
    cout << dp[0] << "\n";

    
    return 0;
}
