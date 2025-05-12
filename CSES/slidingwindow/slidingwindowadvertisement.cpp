#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


const int MAXT = 530000;
const ll inf = 4e18;

struct line {
    ll A, B;
	ll eval(ll x) { return A * x + B; }
	// returns the x-intercept of intersection "strictly" larger than T
	ll cross_after(line &x, ll T) {
        if (x.A == A) {
            return inf;
		}
		ll up = x.B - B;
		ll dn = A - x.A;
		if (dn < 0) {
            dn *= -1;
			up *= -1;
		}
		ll incep = (up <= 0 ? -((-up) / dn) : (up + dn - 1) / dn);
		if (incep > T)
        return incep;
		return inf;
	}
};

struct kst { // min kinetic segment tree
	line tree[MAXT];
	ll melt[MAXT], T;
	int n;
	void pull(int p) {
        ll l = tree[2 * p].eval(T);
		ll r = tree[2 * p + 1].eval(T);
		tree[p] = (l < r || (l == r && tree[2 * p].A < tree[2 * p + 1].A)) ? tree[2 * p] : tree[2 * p + 1];
		melt[p] = min({melt[2 * p], melt[2 * p + 1], tree[2 * p].cross_after(tree[2 * p + 1], T)});
	}
	void init(int s, int e, int p, vector<line> &l) {
        if (s == e) {
            tree[p] = l[s];
			melt[p] = inf;
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p, l);
		init(m + 1, e, 2 * p + 1, l);
        pull(p);
	}
	void update(int pos, line v, int s, int e, int p = 1) {
        if (s == e) {
            tree[p] = v;
			return;
		}
		int m = (s + e) / 2;
		if (pos <= m)
        update(pos, v, s, m, 2 * p);
		else
        update(pos, v, m + 1, e, 2 * p + 1);
		pull(p);
	}
	ll query(int s, int e, int ps, int pe, int p = 1) {
        if (e < ps || pe < s)
        return inf;
		if (s <= ps && pe <= e)
        return tree[p].eval(T);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
	void heaten(int s, int e, int p) {
        if (melt[p] > T)
        return;
		int m = (s + e) / 2;
		heaten(s, m, 2 * p);
		heaten(m + 1, e, 2 * p + 1);
		pull(p);
	}
	void init(vector<line> &l, ll _T) {
        n = sz(l);
		T = _T;
		init(0, n - 1, 1, l);
	}
	void heaten(ll _T) {
        assert(T <= _T);
		T = _T;
		heaten(0, n - 1, 1);
	}
} kst;

// monotonic queue where i < j means h[i] < h[j]
// maximize (r-i) * h[j] = r * h[j] - i * h[j]

// each element has l,r range where a[i] is the min
// either range is fully contained in window or cut on left/right or irrelevant


signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vi left(n, -1), right(n, -1);
    vector<vl> anss;
    rep(it, 0, 2) {
        line emp{0, inf};
        {
            vector<line> init(n, emp);
            kst.init(init, -1);
        }
        deque<pii> q;
        int qstart = 0;
        vl ans;
        rep(i, 0, n) {
            while(sz(q) && q.back().f >= a[i]) {
                q.pop_back();
            }
            int pi = sz(q) ? q.back().s : -1;
            kst.update(qstart + sz(q), line{-a[i], -(-a[i] * pi)}, 0, n-1);
            if(sz(q)) {
                (it ? right : left)[i] = q.back().s;
            }
            q.push_back({a[i], i});
            if(i >= k && q.front().s == i-k) {
                q.pop_front();
                qstart++;
            }
            if(sz(q)) {
                auto [v, idx] = q.front();
                kst.update(qstart, line{-v, -(-v * max(-1LL, i-k))}, 0, n-1);
            }
            // cerr << i << ": " << endl;
            // for(auto [v, idx] : q) {
            //     cerr << v << " " << idx << endl;
            // }
            if(i >= k-1) {
                kst.heaten(i);
                // cerr << "query: " << qstart << " " << sz(q) << endl;
                ans.pb(-kst.query(qstart, qstart+sz(q)-1, 0, n-1));
            }
        }
        anss.pb(ans);
        reverse(all(a));
    }
    reverse(all(anss[1]));
    reverse(all(right));

    vl fans(anss[0]);
    vvi addevents(sz(fans)), remevents(sz(fans));
    rep(i, 0, n) {
        right[i] = n-1-right[i];
        int len = right[i]-1-left[i];
        if(len <= k) {
            int start = max(0LL, right[i]-1-(k-1));
            addevents[start].pb(ll(len) * a[i]);
            int ending = min(n-1, left[i]+1+k-1)-(k-1);
            if(ending+1<sz(remevents))remevents[ending+1].pb(ll(len)*a[i]);
        }
    }
    rep(i, 0, sz(fans)){
        fans[i] = max(fans[i], anss[1][i]);
    }
    multiset<ll> ss;
    rep(i, 0, sz(addevents)){
        for(auto v : addevents[i]) {
            ss.insert(v);
        }
        for(auto v : remevents[i]) {
            ss.erase(ss.find(v));
        }
        if(sz(ss)) fans[i] = max(fans[i], *rbegin(ss));
    }
    for(auto y : fans) cout << y << " ";
    cout << "\n";

    
    return 0;
}
