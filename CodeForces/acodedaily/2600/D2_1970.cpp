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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
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
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
    uniform_int_distribution<int> r30(1, 30);
    uniform_int_distribution<int> rnum(0, (1 << 30)-1);
    uniform_int_distribution<int> r2(0, 1);
    vector<string> s(n);
    map<int, pii> cnt;
    int tries = 0;
    s = vector<string>(n);
    vector<vii> pairs(n);
    rep(i, 0, n){
        rep(j, 0, n){
            pairs[max(i, j)].pb({i, j});
        }
    }
    rep(i, 0, n){
        while(true){
            s[i].clear();
            rep(_, 0, i+1){
                // int split = r30(rng);
                int len = 30;
                int v = rnum(rng);
                // int re = r2(rng);
                rep(j, 0, len){
                    s[i] += ((v >> j) & 1) ? 'X' : 'O';
                }
            }
            bool works = true;
            set<int> cc;
            for(auto [a,b] : pairs[i]){
                string res = s[a] + s[b];
                SuffixArray sa(res);
                int diff = 0;
                rep(t, 1, sz(sa.sa)){
                    diff += sz(res) - sa.sa[t] - sa.lcp[t];
                }
                // cout << res << " " << i << " " << j << " " << diff << endl;
                if(cnt.count(diff) || cc.count(diff)){
                    works = false;
                    break;
                }
                cc.insert(diff);
            }
            tries++;
            // if(tries % 1000 == 0) cout << tries << endl;
            if(!works) continue;
            for(auto [a,b] : pairs[i]){
                string res = s[a] + s[b];
                SuffixArray sa(res);
                int diff = 0;
                rep(t, 1, sz(sa.sa)){
                    diff += sz(res) - sa.sa[t] - sa.lcp[t];
                }
                cnt[diff] = {a, b};
            }
            break;
        }
    }
    rep(i, 0, n) cout << s[i] << endl;
    cerr << tries << endl;
    int q; cin >> q;
    rep(i, 0, q){
        int p; cin >> p;
        auto [a,b] = cnt[p];
        cout << 1+a << " " << 1+b << endl;
    }
    return 0;
}
