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

// ll right;

ll tri(ll n){
    return n * (n + 1) / 2;
}

// IGNORE FIRST
const ll inf = 1e15;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll madd = 0, mn = -inf, sum = 0;
	Node(vl& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			mn = min(l->mn, r->mn);
            sum = l->sum + r->sum;
		}
		else mn = sum = v[lo];
	}
    ll sumq(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return min(l->sumq(L, R), r->sumq(L, R));
	}
    // gets sum of prefix from prev(x) to end()
	ll query(ll x) {
        if(lo + 1 == hi) return mn <= x ? sum : 0;
		push();
        if(r->mn <= x) return l->sum + r->query(x);
        else return l->query(x);
	}

    // gets idx of prev(x)
    ll queryidx(ll x) {
        if(lo + 1 == hi) return mn <= x ? lo : (lo - 1);
		push();
        if(r->mn <= x) return r->queryidx(x);
        else return l->queryidx(x);
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
            sum += (hi - lo) * x;
			mn += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			mn = min(l->mn, r->mn);
            sum = l->sum + r->sum;
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
    int n, m, q; cin >> n >> m >> q;
    vl a(n), b(m);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, m) cin >> b[i];
    for(int i = n - 1; i > 0; i--) a[i] -= a[i - 1];
    for(int i = m - 1; i > 0; i--) b[i] -= b[i - 1];
    ll start = a[0] + b[0];
    vl b1(m - 1);
    rep(i, 0, m - 1) b1[i] = b[i + 1];
    Node tree(b1, 0, m - 1);
    // right = m - 1;
    // rep(i, 0, n) cout << a[i] << " ";
    // cout << nL;
    // rep(i, 0, m) cout << b[i] << " ";
    // cout << nL;
    ll sum = 0;
    rep(i, 0, m - 1){
        sum += b1[i] * (m - 1 - i);
    }
    rep(i, 0, q){
        int t, k, d; cin >> t >> k >> d;
        if(t == 1){
            rep(j, n - k, n) a[j] += d;
            if(k == n) start += d;
        }
        else {
            if(k == m) start += d;
            tree.add(max(0, m - 1 - k), m - 1, d);
            sum += d * tri(min(m - 1, k));
        }

        ll ans = sum + (m + n - 1) * start;
        rep(i, 1, n){
            ll idx = tree.queryidx(a[i]);
            ll val = tree.query(a[i]);
            // all these values got shifted
            ans += val;
            // number of times this value gets used, including self
            ll times = m - 1 - idx + (n - 1 - i);
            ans += times * a[i];
        }
        cout << ans << nL;
        // ll cur = a[0] + b[0], sum = cur;
        // int apnt = 1, bpnt = 1;
        // while(apnt < n || bpnt < m){
        //     if(apnt >= n || (bpnt < m && a[apnt] > b[bpnt])){
        //         cur += b[bpnt++];
        //     }
        //     else cur += a[apnt++];
        //     sum += cur;
        // }
        // cout << sum << nL;
    }
    
    return 0;
}