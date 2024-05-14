#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(string& s, int lim=256) {
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i,1,lim) ws[i] += ws[i-1];
            for(int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i-1], b = sa[i], x[b] = (y[a] == y[b] && 
            y[a + j] == y[b + j]) ? p-1 : p++;
        }
        rep(i,1,n) rank[sa[i]] = i;
        for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i] - 1]; s[i+k] == s[j+k]; k++);
    }
};

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    int n = sz(s);
    string rs(s);
    reverse(all(s));
    SuffixArray sa(s), rsa(rs);
    RMQ<int> lcp(sa.lcp), rlcp(rsa.lcp);
    vi inv(n), rinv(n);
    rep(i, 0, sz(sa.sa)){
        if(sa.sa[i] < n) inv[sa.sa[i]] = i;
        if(rsa.sa[i] < n) rinv[n - 1 - rsa.sa[i]] = i;
    }
    // lcp query
    auto query = [&](int l, int r) -> int {
        if(l > r) swap(l, r);
        return lcp.query(l+1, r+1);
    };
    // lcp query on reverse string
    auto rquery = [&](int l, int r) -> int {
        if (l > r) swap(l, r);
        return rlcp.query(l+1, r+1);
    };
    pll best = {1, 1};
    auto upd = [&](pll a) -> void {
        ll g = __gcd(a.first, a.second);
        a.first /= g, a.second /= g;
        if(best.first * a.second < a.first * best.second) best = a;
    };
    rep(len, 1, n+1){
        for(int i = 0; i < n; i += len){
            int l0 = i, r0 = i + len - 1;
            if(r0 >= n) break;
            int ranges = 1;
            while(i + len + len <= n && query(inv[l0], inv[i + len]) >= len){
                i += len;
                ranges++;
            }
            int l1 = i, r1 = i + len - 1;
            assert(r1 < n);
            int curlen = ranges * len;
            if(l0 > 0){
                int add = min(len, rquery(rinv[l0 - 1], rinv[r0]));
                curlen += add;
            }
            if(r1 + 1 < n){
                int add = min(len, query(inv[l0], inv[r1 + 1]));
                curlen += add;
            }
            upd({curlen, len});
        }
    }
    cout << best.first << "/" << best.second << "\n";

    return 0;
}
