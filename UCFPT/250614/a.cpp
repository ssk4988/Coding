#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

typedef uint64_t ull;
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x ; return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll) 1e11+3;
H hashString(string& s){ H h{}; for(char c : s) h = h*C+c; return h; }

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i, 0, sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b-a];
    }
};

int max_len = 3e5+1;
const int inf = 1e9;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    string s; cin >> s;
    HashInterval hi(s);

    vector<unordered_set<ull>> hashes(max_len);
    vi lens;
    rep(i, 0, n) {
        string t; cin >> t;
        lens.push_back(sz(t));
        hashes[sz(t)].insert(hashString(t).get());
    }

    sort(all(lens));
    lens.erase(unique(all(lens)), end(lens));

    vii intervals;
    vi reach(max_len, -1);
    rep(i, 0, sz(s)) {
        int best = 0;
        for(int l: lens) if(i+l <= sz(s)) {
            if(hashes[l].count(hi.hashInterval(i, i+l).get()))
            best = l;
        }
        reach[i] = i + best;
    }
    int at = 0, ans = 0, furthest = 0;
    rep(i, 0, sz(s)) {
        furthest = max(furthest, reach[i]);
        if(at == i) {
            if(furthest < at) {
                cout << "-1\n";
                return 0;
            }
            at = furthest;
            ans++;
        }
    }
    if(at != sz(s)) {
        cout << "-1\n";
    } else cout << ans << "\n";

    return 0;
}
