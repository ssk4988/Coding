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
	int lo, hi, mset = 0;
    int mn, mx;
    pi data; // min, max
    pi comb(pi a, pi b){
        return {min(a.f, b.f), max(a.s, b.s)};
    }
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			data = comb(l->data, r->data);
		}
		else data = {v[lo], v[lo]};
	}
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return {inf, -inf};
		if (L <= lo && hi <= R) return data;
		push();
		return comb(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R){
            mset = x;
            data.f = data.s = x;
        }
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			data = comb(l->data, r->data);
		}
	}
	void push() {
		if (mset)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = 0;
		// else if (madd)
		// 	l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n), b(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    rep(i, 0, n) cin >> b[i];
    int bidx = 0;
    vi from(n, -1);
    vi start(n, -1);
    vi end(n, -1);
    rep(i, 0, n){
        while(bidx < n && b[bidx] == a[i]){
            from[bidx] = i;
            if(start[i] == -1) start[i] = bidx;
            end[i] = bidx;
            bidx++;
        }
    }
    if(bidx < n){
        cout << -1 << nL;
        return 0;
    }
    queue<int> q;
    vi inq(n);
    Node tree(a, 0, n);
    auto cando = [&](int k) -> bool {
        bool works = true;
        if(start[k] > 0 && (from[start[k] - 1] > start[k] - 1 && !inq[from[start[k] - 1]])) works = false;
        if(end[k] + 1 < n && (from[end[k] + 1] < end[k] + 1 && !inq[from[end[k] + 1]])) works = false;
        return works;
    };
    rep(i, 0, n){
        if(start[i] == -1) continue;
        bool works = true;
        if(cando(i)) {
            q.push(i);
            inq[i] = true;
        }
    }
    vvi ans;
    while(!q.empty()){
        int k = q.front();
        q.pop();
        int curstart = k, curend = k + 1;
        int targetstart = min(curstart, start[k]), targetend = 1 + max(k, end[k]); // end is exclusive
        bool didmax = false, didmin = false;
        while(tree.query(start[k], end[k] + 1) != pi{a[k], a[k]}){
            if(!didmax)
            {
                // do a max command
                // max end where query(curstart, end).max == us
                int lo = curend, hi = targetend;
                while(lo < hi){
                    int mid = lo + (hi - lo + 1) / 2;
                    if(tree.query(curstart, mid).s == a[k]) lo = mid;
                    else hi = mid - 1;
                }
                int newend = lo;
                // min start where query(start, curend).max == us
                lo = targetstart, hi = curstart;
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(tree.query(mid, curend).s == a[k]) hi = mid;
                    else lo = mid + 1;
                }
                int newstart = lo;
                if(tree.query(newstart, newend) != pi{a[k], a[k]}){
                    // does something
                    curstart = newstart;
                    curend = newend;
                    tree.set(newstart, newend, a[k]);
                    ans.push_back({1, newstart + 1, newend});
                    didmax = true;
                    didmin = false;
                }
            }
            if(!didmin)
            {
                // do a min command
                // min end where query(curstart, end).min == us
                int lo = curend, hi = targetend;
                while(lo < hi){
                    int mid = lo + (hi - lo + 1) / 2;
                    if(tree.query(curstart, mid).f == a[k]) lo = mid;
                    else hi = mid - 1;
                }
                int newend = lo;
                // min start where query(start, curend).min == us
                lo = targetstart, hi = curstart;
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(tree.query(mid, curend).f == a[k]) hi = mid;
                    else lo = mid + 1;
                }
                int newstart = lo;
                if(tree.query(newstart, newend) != pi{a[k], a[k]}){
                    // does something
                    curstart = newstart;
                    curend = newend;
                    tree.set(newstart, newend, a[k]);
                    ans.push_back({0, newstart + 1, newend});
                    didmin = true;
                    didmax = false;
                }
            }
        }
        if(start[k] > 0 && !inq[from[start[k] - 1]] && cando(from[start[k] - 1])){
            q.push(from[start[k] - 1]);
            inq[from[start[k] - 1]] = true;
        }
        if(end[k] + 1 > n && !inq[from[end[k] + 1]] && cando(from[end[k] + 1])){
            q.push(from[end[k] + 1]);
            inq[from[end[k] + 1]] = true;
        }
    }
    cout << sz(ans) << nL;
    for(vi &v : ans){
        cout << (v[0] ? 'M' : 'm') << " " << v[1] << " " << v[2] << nL;
    }
    return 0;
}
