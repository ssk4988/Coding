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
        x.pb(0);
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
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; string s, t; cin >> n >> s >> m >> t;
    int x; cin >> x;
    string concat = s + "|" + t;
    SuffixArray sa(concat);
    vi revidxs(n), revidxt(m);
    rep(i, 0, sz(sa.sa)){
        int v = sa.sa[i];
        if(v >= 0 && v < n) revidxs[v] = i;
        else if(v - n - 1 >= 0 && v - n - 1 < m) revidxt[v - n - 1] = i;
    }
    RMQ rmq(sa.lcp);
    vector dp(n+1, vi(x+1, -1));
    // dp[letters from 0 to i, exclusive][segments][i is in a segment]
    // 01 +1 segment, continue extending
    // 00 nothing
    // 10 nothing
    // 11 continue extending
    dp[0][0] = 0;
    rep(i, 0, n){
        rep(j, 0, x+1) {
            if(dp[i][j] == -1) continue;
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            if(j + 1 <= x && dp[i][j] != m) {
                int l = revidxs[i], r = revidxt[dp[i][j]];
                if(l > r) swap(l, r);
                int lcp = rmq.query(l+1, r+1);
                lcp = min({lcp, m - dp[i][j], n - i});
                if(lcp == 0) continue;
                dp[i + lcp][j+1] = max(dp[i + lcp][j + 1], dp[i][j] + lcp);
            }
            // if(j+1 <= x && dp[i][j][0] != -1 && dp[i][j][0] != m && t[dp[i][j][0]] == s[i+1]) dp[i+1][j+1][1] = max(dp[i+1][j+1][1], 1 + dp[i][j][0]);
            // if(dp[i][j][1] != -1 && dp[i][j][1] != m && t[dp[i][j][1]] == s[i+1]) dp[i+1][j][1] = max(dp[i+1][j][1], 1 + dp[i][j][1]);
        }
    }
    bool works = false;
    rep(i, 0, n+1){
        rep(j, 0, x+1){
            if(dp[i][j] == m) {
                works = true;
                // cout << i << " " << j << " " << k << endl;
            }
        }
    }
    cout << (works ? "YES" : "NO") << "\n";
    
    return 0;
}