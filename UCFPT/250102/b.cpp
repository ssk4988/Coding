#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
};

typedef uint64_t ull;
struct H {
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x; return H((ull) m) + (ull)(m >> 64);}
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll) 1e11 + 3;

H hashString(string& s){H h{}; for(char c : s) h = h*C+c;return h; }

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(): ha(1), pw(1,1) {}
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i, 0, sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b-a];
    }
    void push(char c) {
        ha.push_back(ha.back() * C + c);
        pw.push_back(pw.back() * C);
    }
    void pop() {
        ha.pop_back();
        pw.pop_back();
    }
};

string open_br = "([{<";
string close_br = ")]}>";

vector<H> calc(string s, vii rgs) {
    int n = sz(s);
    vvi ends(n);
    for(auto [L, R]: rgs) ends[R].push_back(L);
    // cout << s << endl;
    // for(auto [L, R]: rgs) cout << L << ' ' << R << endl;

    vii stk;
    HashInterval hi;
    int start = -1;
    
    vector<FT> fts(4, FT(n));

    vector<H> res;

    rep(i, 0, n) {
        if(start == -1) {
            if(close_br.find(s[i]) != string::npos)
                start = i;
            continue; 
        }

        int idx = open_br.find(s[i]);
        // cout << i << ' ' << idx << endl;
        if(idx != string::npos) {
            stk.emplace_back(i, idx);
            hi.push(s[i]);
        }
        else {
            idx = close_br.find(s[i]);
            if(sz(stk) == 0 || idx != stk.back().second) {
                start = -1;
                stk = vii();
                hi = HashInterval();
                // cout << "HERE\n";
                continue;
            }

            fts[idx].update(i, -1);
            fts[idx].update(stk.back().first, 1);

            stk.pop_back();
            hi.pop();
        }

        for(int L: ends[i]) {
            cout << "RANGE: " << L << ' ' << i << ' ' << s.substr(L, i - L + 1) << endl;
            if(L < start) continue;
            bool bad = false;
            rep(idx, 0, 4) if(fts[idx].query(L))
                bad = true;
            if(bad) continue;
            
            int idx = lower_bound(all(stk), pii(L, -1)) - begin(stk);
            cout << L << ' ' << i << ' ' << s.substr(L, i - L + 1) << '\n';
            cout << stk[idx].first << '\n';
            cout << "SUBSTRING HASH: ";
            rep(i, idx, sz(stk)) cout << open_br[stk[i].second];
            cout << '\n';
            res.push_back(hi.hashInterval(idx, sz(stk)));
        }
    }

    return res;
}

void solve() {
    cout << "NEW CASE\n";
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vii rgs(m);
    for(auto &[L, R]: rgs)
        cin >> L >> R, L--, R--;

    // compute forwards
    auto fwd = calc(s, rgs);

    // reflect
    reverse(all(s));
    for(char &c: s) {
        int idx = open_br.find(c);
        if(open_br.find(c) != string::npos) {
            c = close_br[idx];
            continue; 
        }
        idx = close_br.find(c);
        c = open_br[idx];
    }

    for(auto &[L, R]: rgs) {
        swap(L, R);
        L = n - L - 1, R = n - R - 1;
    }

    // compute backwards
    cout << "REFLECTED" << '\n';
    auto ref = calc(s, rgs);

    unordered_map<ull, int> frq;
    int balanced = 0;
    for(H h: fwd) {
        if(h == 0) balanced++;
        else frq[h.get()]++;
    }

    cout << "BALANCED: " << balanced << '\n';

    int res = balanced / 2;
    for(H h: ref) if(!(h == 0) && frq[h.get()])
        res++, frq[h.get()]--;
    
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}

/*
RANGE: 2 7 {}<<<<
RANGE: 16 19 ]){(
RANGE: 19 20 ()
19 20 ()
19
SUBSTRING HASH: 
RANGE: 18 21 {()}
18 21 {()}
18
SUBSTRING HASH: 
RANGE: 20 21 )}
REFLECTED
BALANCED: 2
1
*/
