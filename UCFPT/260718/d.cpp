#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

typedef uint64_t ull;
struct H {
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x; return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll) 1e11+3;

H hashString(string s){H h{}; for(char c : s) h = h * C + c; return h; }

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i, 0, sz(str)) 
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b - a];
    }
};

vector<H> pw;
int k;

// store first min(n*m, k) letters
map<H, int> freq;
// map<int, H> bases;
H getbase(int l, int len) {
    // if(bases.count(l)) return bases[l];
    H ans;
    for(int p = 0; p < len; p += l) ans = ans + pw[p];
    return ans;
}
int tot = 0;

vector<vector<char>> rot(vector<vector<char>> &grid) {
    int n = sz(grid), m = sz(grid[0]);
    vector<vector<char>> grid2(m, vector<char>(n));
    rep(i, 0, n) rep(j, 0, m) {
        grid2[j][n-1-i] = grid[i][j];
    }
    return grid2;
}

void solve(auto grid, int dr, int dc) {
    int n = sz(grid), m = sz(grid[0]);
    // cerr << "solving: " << dr << " " << dc << endl;
    rep(i, 0, n) {
        // rep(j, 0, m) cerr << grid[i][j];
        // cerr << endl;
    }
    int len = 0;
    {
        int i = 0, j = 0;
        do {
            i = (i + dr) % n, j = (j + dc) % m;
            len++;
        } while(!(i == 0 && j == 0));
    }
    H base = getbase(len, k / len * len);
    vvi seen(n, vi(m));
    rep(si, 0, n) {
        rep(sj, 0, m) {
            if(seen[si][sj]) continue;
            string pattern;
            {
                int i = si, j = sj;
                while(!seen[i][j]) {
                    seen[i][j] = 1;
                    pattern += grid[i][j];
                    i += dr, j += dc;
                    i %= n, j %= m;
                }
            }
            HashInterval ha(pattern);
            rep(r, 0, len) {
                H rot = ha.hashInterval(r, len) * pw[r] + ha.hashInterval(0, r);
                int split = max(0, r + k % len - len);
                H left = ha.hashInterval(r, min(len, r + k % len)) * pw[split] + ha.hashInterval(0, split);
                H comb = rot * base * pw[k % len] + left;
                // cerr << "pattern " << pattern << " rot: " 
                // << r << " makes " << pattern.substr(r, len - r) 
                //     << pattern.substr(0, r) << " with extra " 
                //     << pattern.substr(r, min(len, r + k % len) - r) << pattern.substr(0, split) 
                //     << " gives hash " << comb.get() << " patthash " << (rot*base).get() << " extra hash " 
                //     << left.get() << " base is " << base.get() << endl;
                freq[comb]++;
                tot++;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m >> k;
    k = min(k, n*m);
    vector<vector<char>> grid(n, vector<char>(m));
    pw.push_back(1);
    rep(i, 0, n) rep(j, 0, m) {
        cin >> grid[i][j];
        pw.push_back(pw.back() * C);
    }
    

    rep(_, 0, 4) {
        solve(grid, 0, 1);
        solve(grid, 1, 1);
        grid = rot(grid);
    }
    ll num = 0;
    ll denom = ll(tot) * tot;
    for(auto [k, v] : freq) {
        // cerr << k.get() << ": " << v << endl;
        num += ll(v) * v;
    }
    // cerr << "tot: " << tot << endl;
    // cerr << hashString("ab"s).get() << " " << hashString("aa"s).get() << " " << hashString("bb"s).get() << endl;
    ll g = gcd(num, denom);
    num /= g;
    denom /= g;
    cout << num << "/" << denom << "\n";
    return 0;
}
