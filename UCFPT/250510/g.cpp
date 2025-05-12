#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

typedef uint64_t ull;
struct H
{
    ull x;
    H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t) x * o.x; return H((ull)m) + (ull) (m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }

};
static const H C = (ll)1e11+3;

H hashString(string& s) { H h{}; for(char c : s) h = h*C + c; return h;}


struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str): ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,0,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
            
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b-a];
    }
};


vvi solve(vector<string> grid) {
    int n = sz(grid), m = sz(grid[0]);
    vvi res(n, vi(m));
    rep(i, 0, n) {
        string rev(all(grid[i]));
        reverse(all(rev));
        HashInterval ha(grid[i]), ah(rev);
        vvi addevents(m+1), remevents(m+1);
        rep(l, 0, m) {
            int maxr = 0;
            rep(r, l+1, m+1) {
                H forward = ha.hashInterval(l, r), backward = ah.hashInterval(m-r, m-l);
                if(forward == backward) {
                    maxr = r;
                }
            }
            addevents[l].push_back(maxr-l);
            remevents[maxr].push_back(maxr-l);

        }
        multiset<int> s;
        rep(l, 0, m) {
            for(int v : addevents[l]) {
                s.insert(v);
            }
            for(int v : remevents[l]) {
                s.erase(s.find(v));
            }
            if(sz(s)) {
                res[i][l] = *rbegin(s);
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    vector<string> tgrid(m, string("a", n));
    rep(i, 0, n) {
        cin >> grid[i];
        rep(j, 0, m) {
            tgrid[j][i] = grid[i][j];
        }
    }
    vvi a = solve(grid), b = solve(tgrid);
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            ans = max(ans, a[i][j] * b[j][i]);
        }
    }
    cout << ans << "\n";
    return 0;
}
