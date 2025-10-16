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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};



void solve() {
    string s; cin >> s;
    int n = sz(s);
    int q; cin >> q;
    using a3 = array<int, 3>;
    set<a3> rng;
    SuffixArray sa(s);
    vi inv(n+1);
    RMQ rmq(sa.lcp);
    auto lcp = [&](int i, int j) {
        if(i > j) swap(i, j);
        if(i == j) return n-i;
        return rmq.query(i+1, j+1);
    };
    rep(i, 0, sz(sa.sa)) inv[sa.sa[i]] = i;
    vl pref(sz(sa.sa)+1);
    rep(i, 0, sz(sa.sa)) {
        int val = i == 0 ? 0 : n-sa.sa[i]-sa.lcp[i];
        pref[i+1] = pref[i] + val;
    }
    // return if a contains b
    auto contains = [&](a3 a, a3 b) {
      return a[2] <= b[2] && a[0] <= b[0] && -b[1] <= -a[1];  
    };
    auto score = [&](a3 a) {
        auto [l, r, len] = a;
        r *= -1;
        return pref[r]-pref[l+1]+(n-sa.sa[l]-(len-1));
    };
    ll ans = 0;
    // rep(i, 0, sz(sa.sa)) {
    //     cerr << sa.sa[i] << " " << s.substr(sa.sa[i]) << endl;
    // }
    rep(i, 0, q) {
        int l, r; cin >> l >> r; l--;
        // max where suffix < [l,r), +1
        // min where suffix >= [l, r)
        int l2 = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            int cur = l2 + dif;
            if(cur >= sz(sa.sa)) continue;
            int val = lcp(cur, inv[l]);
            if(val >= min(r-l, n-sa.sa[cur])) {
                if(r-l > n-sa.sa[cur]) l2 = cur;
            } else {
                if(inv[l] > cur) l2 = cur;
            }
        }
        l2++;
        // min where suffix > [l, r)
        int r2 = -1;
        for(int dif = 1 << 20; dif; dif /= 2) {
            int cur = r2 + dif;
            if(cur >= sz(sa.sa)) continue;
            int val = lcp(cur, inv[l]);
            if(val >= min(r-l, n-sa.sa[cur])) {
                r2 = cur;
            } else {
                if(inv[l] >= cur) r2 = cur;
            }
        }
        r2++;
        // cerr << "l2 " << l2 << " r2 " << r2 << endl;
        a3 cur{l2, -r2, r-l};
        auto bef = rng.upper_bound(cur);
        bool insert = true;
        if(bef != begin(rng)) {
            bef--;
            if(contains(*bef, cur)) insert = false;
        }
        if(insert) {
            while(true) {
                auto it = rng.lower_bound(cur);
                if(it == end(rng) || !contains(cur, *it)) break;
                ans -= score(*it);
                rng.erase(it);
            }
            rng.insert(cur);
            ans += score(cur);
        }
        // cerr << "set:\n";
        // for(auto [a, b, c] : rng) {
        //     cerr << a << " " << -b << " " << c << endl;
        // }
        cout << ans << " ";
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    
    return 0;
}
