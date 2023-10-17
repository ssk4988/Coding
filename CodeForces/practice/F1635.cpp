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

const ll inf = 5e18;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll val = inf;
	// Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			val = min(l->val, r->val);
		}
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			val = x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vl x(n), w(n);
    rep(i, 0, n){
        cin >> x[i] >> w[i];
    }
    Node left(0, n), right(0, n);
    stack<pl> st;
    vvi fromright(n), fromleft(n);
    // fromright[i]: all j so that earliest left is i
    rep(i, 0, n){
        pl nex = {w[i], i};
        while(sz(st) && st.top() > nex) st.pop();
        if(sz(st)){
            fromright[st.top().s].pb(i);
        }
        st.push(nex);
    }
    while(sz(st)) st.pop();
    for(int i = n - 1; i >= 0; i--){
        pl nex = {w[i], i};
        while(sz(st) && st.top() > nex) st.pop();
        if(sz(st)){
            fromleft[st.top().s].pb(i);
        }
        st.push(nex);
    }
    vvi fromqleft(n), fromqright(n);
    vpi qs(q);
    vl ans(q, inf);
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--, b--;
        fromqleft[b].pb(i);
        fromqright[a].pb(i);
        qs[i] = {a, b};
    }
    for(int i = n- 1; i >= 0; i--){
        for(int j : fromright[i]){
            ll cost = abs(x[j] - x[i]) * (w[j] + w[i]);
            right.add(j, j + 1, cost);
        }
        for(int idx : fromqright[i]){
            auto [a, b] = qs[idx];
            ans[idx] = min(ans[idx], right.query(a, b + 1));
        }
    }
    for(int i = 0; i < n; i++){
        for(int j : fromleft[i]){
            ll cost = abs(x[j] - x[i]) * (w[j] + w[i]);
            left.add(j, j + 1, cost);
        }
        for(int idx : fromqleft[i]){
            auto [a, b] = qs[idx];
            ans[idx] = min(ans[idx], left.query(a, b + 1));
        }
    }
    rep(i, 0, q){
        cout << ans[i] << nL;
    }
    
    return 0;
}
