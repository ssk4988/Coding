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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
		x.push_back(0), sa = lcp = y, iota(all(sa), 0);
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
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

void solve() {
    int k; string str; cin >> k >> str;
    SuffixArray sa(str);
    int n = sz(str);
    vi inv(n);
    rep(i, 0, sz(sa.sa)) {
        if(sa.sa[i] < n) inv[sa.sa[i]] = i;
    }
    int start = 0;
    string res;
    for(char c = 'z'; c >= 'a'; c--){
        if(k == 0) continue;
        vpi rs;
        rep(i, start, n) {
            if(str[i] != c) continue;
            if(sz(rs) == 0 || rs.back().s != i) {
                rs.emplace_back(i, i+1);
            } else rs.back().s++;
        }
        vpi use;
        if (sz(rs) && rs[0].f == start) {
            use.push_back(rs[0]);
            rs.erase(begin(rs));
        }
        sort(begin(rs), end(rs), [&](pi a, pi b) -> bool { return a.s - a.f > b.s - b.f || (a.s - a.f == b.s - b.f && a < b); });
        // if(sz(rs)) k--;
        int pnt = 0;
        while (pnt < sz(rs) && k > 1) {
            use.push_back(rs[pnt++]);
            k--;
        }
        rs.erase(begin(rs), begin(rs) + pnt);
        if(sz(rs) && k == 1) {
            sort(all(rs), [&](pi a, pi b) -> bool { return a.s - a.f > b.s - b.f || (a.s - a.f == b.s - b.f && inv[a.f] > inv[b.f]); });
            k--;
            use.push_back(rs[0]);
        }
        sort(all(use));
        for(auto [tl, tr] : use) {
            rep(i, tl, tr) res.pb(str[i]);
        }
        if (sz(use)) start = use.back().s;
    }
    rep(i, start, n) {
        res.pb(str[i]);
    }
    cout << res << "\n";
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
