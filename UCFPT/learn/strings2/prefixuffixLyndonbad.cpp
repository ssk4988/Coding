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
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct SuffixArray
{
    vi sa, lcp;
    SuffixArray(string &s, int lim = 256)
    { // or basic_string<int>
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p)
        {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;)
                sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1];
                 s[i + k] == s[j + k]; k++)
                ;
    }
};

template <class T>
struct RMQ
{
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V)
    {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
        {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b)
    {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
    H rotInterval(int start, int mid, int end) {
        return hashInterval(mid, end) * pw[mid - start] + hashInterval(start, mid);
    }
};

const int LOG = 23;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    string str;
    cin >> str;
    string fr = str.substr(0, n / 2), ba = str.substr(n - n / 2);

    // generate min rotations of prefixes of fr
    vi rotdp(sz(fr));
    set<H> prefrots;
    {
        int n = sz(fr);
        SuffixArray sa(fr);
        RMQ<int> lcp(sa.lcp);
        vi inv(n);
        rep(i,0, sz(sa.sa)){
            if(sa.sa[i] < n) inv[sa.sa[i]] = i;
        }
        auto query = [&](int l, int r) ->int {
            l = inv[l], r = inv[r];
            if(l > r) swap(l, r);
            return lcp.query(l+1, r+1);
        };
        int i = 0;
        // vector<string> factorization;
        while (i < n)
        {
            int j = i + 1, k = i;
            rotdp[i] = i;
            while (j < n && fr[k] <= fr[j])
            {
                bool matched = false;
                if (fr[k] < fr[j])
                    k = i;
                else
                    matched = true, k++;
                j++;
                if((k - i) % (j - k) == 0){
                    // made a copy or still making word
                    rotdp[j-1] = i;
                } else {
                    // partial match of previous word
                    int totlen = j;
                    int l = min(totlen - k, query(k, 0));
                    rotdp[j-1] = rotdp[k-1];
                    if(l == totlen - k) {
                        l = min(k, query(0, totlen - k));
                        if(l == k) {
                            // use previous word, so do nothing
                        } else if(fr[0 + l] > fr[totlen - k + l]) {
                            rotdp[j-1] = j - ((k - i) % (j - k));
                        }
                    } else {
                        if (fr[k + l] > fr[0 + l]) rotdp[j-1] = j - ((k - i) % (j - k));
                    }
                }
            }
            while (i <= k)
            {
                // factorization.push_back(fr.substr(i, j - k));
                i += j - k;
            }
        }
        HashInterval ha(fr);
        rep(i, 0, n){
            // cout << rotdp[i] << " ";
            prefrots.insert(ha.rotInterval(0, rotdp[i], i+1));
        }
        // cout << "\n";
    }
    int ans = 0;
    // generate min rotations of suffixes of ba
    {
        int n = sz(ba);
        SuffixArray sa(ba);
        RMQ<int> lcp(sa.lcp);
        vi inv(n);
        vi link(n+1);
        vi diff(n+1);
        vi runcnt(n+1);
        vi runnxt(n+1);
        vi logrun(n+1);
        link[n] = n;
        runcnt[n] = 0;
        runnxt[n] = n;
        logrun[n] = n;
        auto query = [&](int l, int r) ->int {
            l = inv[l], r = inv[r];
            if(l > r) swap(l, r);
            return lcp.query(l+1, r+1);
        };
        set<int> sufinsert;
        rep(i, 0, sz(sa.sa)){
            if(sa.sa[i] < n) {
                inv[sa.sa[i]] = i;
                link[sa.sa[i]] = *sufinsert.upper_bound(sa.sa[i]);
            }
            sufinsert.insert(sa.sa[i]);
        }
        for(int i = n-1; i >= 0; i--){
            diff[i] = link[i] - i;
            runcnt[i] = runcnt[link[i]];
            if(diff[i] == diff[link[i]] && query(i, link[i]) >= diff[i]){
                // is part of the run
                runnxt[i] = runnxt[link[i]];
            } else {
                // new run
                runcnt[i]++;
                runnxt[i] = link[i];
            }
            logrun[i] = runcnt[i] <= LOG ? i : logrun[link[i]];
        }
        HashInterval ha(ba);
        rep(i, 0, n){
            int cur = logrun[i];
            while(runcnt[cur]) {
                int l = cur + diff[cur] == n ? 0 : query(cur, cur + diff[cur]);
                // cout << "run candidate " << i << " " << cur << " " << n << "\n";
                if(l >= n - (cur + diff[cur])){
                    // candidate for min rotation
                    bool works = l % diff[cur] == 0;
                    if(!works) {
                        // partial match needs to made whole match
                        int part = l % diff[cur];
                        if(query(i, cur + part) >= diff[cur] - part) works = true;
                    }
                    if(works) {
                        // cout << "try " << i << " " << cur << " " << n << "\n";
                        H hsh = ha.rotInterval(i, cur, n);
                        if(prefrots.count(hsh)){
                            // cout << "matched\n";
                            ans = max(ans, n - i);
                        }
                    }
                }
                cur = runnxt[cur];
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
