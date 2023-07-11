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
	int lo, hi;
    pi val;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			comb();
		}
        else val = {-inf, lo};
	}
    pi combine(pi l, pi r){
        return max(l, r);
    }
    void comb(){
        val = combine(l->val, r->val);
    }
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return {-inf, -1};
		if (L <= lo && hi <= R) return val;
		return combine(l->query(L, R), r->query(L, R));
	}
	void pointupd(int idx, int v){
		if (lo + 1 == hi){
			// do the update
            val.f = v;
		}
		else {
			int mid = lo + (hi - lo) / 2;
			if(mid <= idx) r->pointupd(idx, v);
			else l->pointupd(idx, v);
			comb();
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vpi ints(m);
    vi open(n + 1, INT_MAX); // min a for intervals where b >= x
    vi closed(n + 2); // max a for intervals where b < x
    rep(i, 0, m){
        cin >> ints[i].f >> ints[i].s;
        open[ints[i].s] = min(open[ints[i].s], ints[i].f);
        closed[ints[i].s + 1] = max(closed[ints[i].s + 1], ints[i].f);
    }
    rep(i, 1, sz(closed)) closed[i] = max(closed[i], closed[i - 1]);
    for(int i = sz(open) - 1 - 1; i >= 0; i--) open[i] = min(open[i], open[i + 1]);
    vpi dp(n + 1, {-1, -1});
    dp[0].f = 0;
    Node tree(0, n + 1);
    tree.pointupd(0, 0);
    rep(i, 1, n + 1){
        int left = closed[i], right = open[i];
        if(left >= right) continue; // impossible to put something here
        pi pre = tree.query(left, right);
        pre.f++;
        dp[i] = pre;
        tree.pointupd(i, dp[i].f);
    }
    int best = 0;
    rep(i, 0, n + 1) if(dp[best].f <= dp[i].f) best = i;
    vi occ(n + 1);
    int cur = best;
    while(cur > 0){
        occ[cur]++;
        cur = dp[cur].s;
    }
    rep(i, 1, sz(occ)) occ[i] += occ[i - 1];
    bool works = true;
    rep(i, 0, m){
        if((occ[ints[i].s] - occ[ints[i].f - 1]) != 1) works = false;
    }
    // cout << dp[n] << nL;
    if(!works) cout << -1 << nL;
    else cout << dp[best].f << nL;
    
    return 0;
}