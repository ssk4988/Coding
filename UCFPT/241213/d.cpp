#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) x.size()

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw*2 + 1);
			rep(j,0,sz(jmp[k])) jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
		}
	}
	T query(int a, int b) {
		assert(a != b);
        if(a > b) swap(a, b);
		int dep = 31-__builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b-(1 << dep)]);
	}
};

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(string &s, int lim=256) {
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j*2), lim = p) {
            p = j, iota(all(y), n-j);
            rep(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i-1];
            for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i-1], b = sa[i], x[b] = (y[a] == y[b] && y[a+j] == y[b+j]) ? p-1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for(int i = 0, j; i < n-1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i]-1]; s[i+k] == s[j+k]; k++);
    }
};

void solve() {
    int n; cin >> n;
    string s, t; cin >> s >> t; t = "A" + t;
    string rs(s);
    reverse(all(rs));
    string rt(t);
    reverse(all(rt));
    string st = s + t;
    string ts = rt + rs;
    SuffixArray sast(st), sats(ts);
    RMQ rmq(sast.lcp), rmqr(sats.lcp);
    vi inv(sz(st)+1), rinv(sz(st)+1);
    rep(i, 0, sz(sast.sa)){
        inv[sast.sa[i]] = i;
        rinv[sats.sa[i]] = i;
    }
    int ans = 0;
    for(int len = 1; len <= n; len++){
        vi idxs;
        for(int i = 0; i < n; i += len) {
            for(int sgn : {-1, 1}){
                for(int d : {0, len/2, (len+1)/2}){
                    int idx = i + sgn * d;
                    if(idx >= 0 && idx < n) idxs.push_back(idx);
                }
            }
        }
        sort(all(idxs));
        idxs.erase(unique(all(idxs)), end(idxs));
        for(int i : idxs){
        // for(int i = 0; i < n; i += len) {
            if(i + len + len <= n) {
                // same string
                int common = rmq.query(inv[i]+1, inv[i+len]+1);
                if(common >= len) ans = max(ans, len);
                common = rmq.query(inv[n+1+i]+1, inv[n+1+i+len]+1);
                if(common >= len) ans = max(ans, len);
            }
            if(i + len + len <= n+1) {
                // diff string
                // more in top
                int pref = min(len, rmq.query(inv[i]+1, inv[i+len]+1));
                int suff = min(len, rmqr.query(rinv[2*n+1-1-(i+len-1)]+1, rinv[2*n+1-1-(n+i+len+len-1)]+1));
                if(pref + suff >= len) ans = max(ans, len);
                // more in bottom
                suff = min(len, rmqr.query(rinv[2*n+1-1-(n+i+len-1)]+1, rinv[2*n+1-1-(n+i+len+len-1)]+1));
                pref = min(len, rmq.query(inv[i]+1, inv[n+i+len]+1));
                if(pref + suff >= len) ans = max(ans, len);
            }
            if(i > 0 && i + len < n) {
                // same string, not aligned
                int pref = min(len, rmq.query(inv[i]+1, inv[i+len]+1));
                int suff = min(len, rmqr.query(rinv[2*n+1-1-(i+len-1)]+1, rinv[2*n+1-1-(i-1)]+1));
                if(pref + suff >= len) ans = max(ans, len);
                pref = min(len, rmq.query(inv[n+1+i]+1, inv[n+1+i+len]+1));
                suff = min(len, rmqr.query(rinv[2*n+1-1-(n+1+i+len-1)]+1, rinv[2*n+1-1-(n+1+i-1)]+1));
                if(pref + suff >= len) ans = max(ans, len);
            }
            if(i > 0 && i + len <= n)
            {
                // diff string, middle belongs to top
                int left = min(len, rmqr.query(rinv[2*n+1-1-(i+len-1)]+1, rinv[2*n+1-1-(i-1)]+1));
                int right = i + len < n ? min(len, rmq.query(inv[i]+1, inv[i+len]+1)) : 0;
                if(left + right < len && n+i+len+len-1-left < sz(st)) {
                    int leftr = min(len, rmqr.query(rinv[2*n+1-1-(n+i+len+len-1-left)]+1, rinv[2*n+1-1-(i+len-1-left)]+1));
                    if(left + right + leftr >= len) ans = max(ans, len);
                }
            }
            if(i > 0 && n+i+len < sz(st))
            {
                // diff string, middle belongs to bottom
                int right = min(len, rmq.query(inv[n+i]+1, inv[n+i+len]+1));
                int left = min(len, rmqr.query(rinv[2*n+1-1-(n+i-1)]+1, rinv[2*n+1-1-(n+i-1+len)]+1));
                if(left + right < len && i-len+right >= 0) {
                    int rightl = min(len, rmq.query(inv[i-len+right]+1, inv[n+i+right]+1));
                    if(left + right + rightl >= len) ans = max(ans, len);
                }
            }
        }
    }
    cout << 2 * ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    // int t; cin >> t;
    // while (t--) 
    solve();

    return 0;
}
