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

using a2 = array<int, 2>;

const int inf = 1e9;
struct Digs{
    vector<a2> mn;
    Digs() : mn(9, {inf, inf}){}
    Digs operator+(Digs &d){
        Digs res;
        rep(i, 0, sz(res.mn)){
            int a = 0, b = 0;
            rep(j, 0, 2){
                if(mn[i][a] < d.mn[i][b]){
                    res.mn[i][j] = mn[i][a++];
                }
                else res.mn[i][j] = d.mn[i][b++];
            }
        }
        return res;
    }
    void add(int x){
        mn.assign(9, {inf, inf});
        int x1 = x;
        for(int i = 0; i < sz(mn) && x1 > 0; i++, x1 /= 10){
            if(x1 % 10 != 0) {
                mn[i][0] = x;
            }
        }
    }
};

const Digs emp;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    Digs val;
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi){
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val + r->val;
		}
		else {val.add(v[lo]);}
	}
	Digs query(int L, int R) {
		if (R <= lo || hi <= L) return emp;
		if (L <= lo && hi <= R) return val;
        Digs l1 = l->query(L, R), r1 = r->query(L, R);
		return l1 + r1;
	}
	void set(int L, int x) {
		if (lo + 1 == hi) {
            val.add(x);
        }
		else {
            int mid = lo + (hi - lo) / 2;
            if(mid <= L) r->set(L, x);
            else l->set(L, x);
			val = l->val + r->val;
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    Node tree(a, 0, n);
    rep(i, 0, m){
        int t; cin >> t;
        if(t == 1){
            int idx, x; cin >> idx >> x; idx--;
            tree.set(idx, x);
        }
        else{
            int l, r; cin >> l >> r; l--, r--;
            Digs res = tree.query(l, r + 1);
            ll ans = LLONG_MAX;
            rep(j, 0, sz(res.mn)){
                if(res.mn[j][1] != inf)
                    ans = min(ans, ll(res.mn[j][0]) + res.mn[j][1]);
            }
            if(ans == LLONG_MAX) ans = -1;
            cout << ans << nL;
        }
    }
    
    return 0;
}
