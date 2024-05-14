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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
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

    string str;
    while(cin >> str) {
        if(str == "0") break;
        int n = sz(str);
        string revstr(str);
        reverse(all(revstr));
        SuffixArray sa(str), rsa(revstr);
        vi inv(n), rinv(n);
        rep(i, 0, sz(sa.sa)){
            if(sa.sa[i] < n) inv[sa.sa[i]] = i;
            if(rsa.sa[i] < n){
                rsa.sa[i] = n - 1 - rsa.sa[i];
                rinv[rsa.sa[i]] = i;
            }
        }
        RMQ<int> lcp(sa.lcp), rlcp(rsa.lcp);
        ll ans = 0;
        rep(len, 1, n+1){
            vii buckets;
            for(int i = 0; i < n; i += len){
                buckets.pb({i, min(n, i + len) - 1});
            }
            rep(i, 0, sz(buckets)-1){
                auto [l0, r0] = buckets[i];
                auto [l1, r1] = buckets[i+1];
                int le = rinv[r0], ri = rinv[r1];
                if(le > ri) swap(le, ri);
                int suff = min({r0 - l0 + 1, r1 - l1 + 1, rlcp.query(le+1, ri+1)});
                int pref = 0;
                if(i + 2 < sz(buckets)){
                    auto [l2, r2] = buckets[i+2];
                    le = inv[l1], ri = inv[l2];
                    if(le > ri) swap(le, ri);
                    pref = min({r1 - l1 + 1, r2 - l2 + 1, lcp.query(le+1, ri+1)});
                }
                int cont = max(0, min({len, suff, suff + pref + 1 - len}));
                ans += cont;
            }
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
