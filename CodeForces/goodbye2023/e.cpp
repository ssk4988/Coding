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
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = max(l->val, r->val);
		}
		else val = 0;
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int n;
ll ans;
vi eul, eulidx, eulend;
vi par, a, pre;
vvi child, bucket;
Node *tree = NULL;
void dfs(int u){
    int preval = pre[a[u]];
    eulidx[u] = sz(eul);
    eul.pb(u);
    if(preval != -1){
        bucket[preval].pb(u);
    }
    pre[a[u]] = u;
    for(int v : child[u]){
        dfs(v);
    }
    eulend[u] = sz(eul);
    pre[a[u]] = preval;
}

void calcdfs(int u){
    for(int v : child[u]){
        calcdfs(v);
    }
    tree->add(eulidx[u], eulend[u], 1);
    for(int v : bucket[u]){
        tree->add(eulidx[v], eulend[v], -1);
        // for(int w : bucket[v]){
        //     tree->add(eulidx[w], eulend[w], 1);
        // }
    }
    vl best(2, 1);
    best.pb(tree->query(eulidx[u], eulidx[u] + 1));
    for(int v : child[u]){
        best.pb(tree->query(eulidx[v], eulend[v]));
    }
    sort(all(best));
    reverse(all(best));
    ans = max(ans, best[0] * best[1]);
}

void solve(){
    // WATCH OUT MEMORY
    cin >> n;   
    ans = 1;
    tree = new Node(0, n);
    par = vi(n);
    eul.clear();
    eulend = vi(n);eulidx = vi(n);
    a = vi(n);
    pre = vi(n, -1);
    child = vvi(n);
    bucket = vvi(n);
    rep(i, 1, n){
        cin >> par[i];
        par[i]--;
        child[par[i]].pb(i);
    }
    rep(i, 0, n){
        cin >> a[i]; a[i]--;
    }
    dfs(0);
    calcdfs(0);
    cout << ans << nL;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    
    return 0;
}
