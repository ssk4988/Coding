#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

vi Z(const string& S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i,1,sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while(i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}
typedef uint64_t ull;
struct H{
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t) x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get()  == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll) 1e11 + 3;

H hashString(string& s) { H h{}; for(char c : s) h = h * C + c; return h; }


struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,0,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b - a];
    }
    void addc(char c) {
        pw.push_back(pw.back() * C);
        ha.push_back(ha.back() * C + c);
    }
};


const int K = 600;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    int last = 0;
    string s;
    string buf;
    string emptystr = "";
    HashInterval ha(emptystr);
    vi z;
    vi suff{0};
    rep(qid, 0, q) {
        string t; cin >> t;
        if(t == "add") {
            char v; cin >> v;
            char c = ((v - 'a' + last) % 26) + 'a';
            ha.addc(c);
            buf.push_back(c);
            if(sz(buf) == K) {
                s += buf;
                z = Z(s);
                z[0] = sz(s);
                suff = vi(sz(s)+1);
                for(int i : z) {
                    suff[i]++;
                }
                for(int i = sz(suff)-2; i >= 0; i--) suff[i] += suff[i+1];
                buf = "";
                // cerr << "s: " << s << endl;
                // cerr << "buf: " << buf << endl;
                // for(int i : z) cerr << i << " ";
                // cerr << 
            }
        } else {
            int n = sz(s) + sz(buf);
            int k; cin >> k;
            k = (k-1 + last + n) % n + 1;
            int ans = 0;
            if(k < sz(suff)) ans += suff[k];
            H target = ha.hashInterval(0, k);
            rep(i, sz(s)+1, sz(s) + sz(buf)+1) {
                if(i - k < 0) continue;
                H sub = ha.hashInterval(i - k, i);
                ans += sub == target;
            }
            last = ans;
            cout << ans << "\n";
        }
    }
    return 0;
}
