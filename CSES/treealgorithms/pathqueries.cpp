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

const ll inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, val = 0;
	Node(ll lo,ll hi):lo(lo),hi(hi){} // Large llerval of -inf
	Node(vl& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = (l->val + r->val);
		}
		else val = v[lo];
	}
	ll query(ll L, ll R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		return (l->query(L, R) + r->query(L, R));
	}
	void set(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) val = x;
		else {
			l->set(L, R, x), r->set(L, R, x);
			val = (l->val + r->val);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int siz = 0;
    vl euler(2 * n + 5), dfsorder1(n), dfsorder2(n), treesz(n, 1);
    auto dfs = [&](int cur, int pre, auto &&dfs)->void{
        dfsorder1[cur] = siz;
        euler[siz++] = a[cur];
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs(i, cur, dfs);
            treesz[cur] += treesz[i];
        }
        dfsorder2[cur] = siz;
        euler[siz] = -a[cur];
        siz++;
    };
    dfs(0, -1, dfs);
    Node *tree = new Node(euler, 0, sz(euler));
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int s, x; cin >> s >> x;s--;
            tree->set(dfsorder1[s], dfsorder1[s] + 1, x);
            tree->set(dfsorder2[s], dfsorder2[s] + 1, -x);
        }
        else{
            int s; cin >> s; s--;
            cout << tree->query(0, dfsorder1[s] + 1) << nL;
        }
    }



    
    return 0;
}