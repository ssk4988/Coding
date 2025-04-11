#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define f first
#define s second

random_device rdev;
mt19937 rng(rdev());

// const int mod = 1e9+9;
// const int C = 998244353;

// struct H{
//     int x; H(int x=0) : x(x) {}
//     H operator+(H o) { return (x+o.x)%mod; }
//     H operator-(H o) { return (x-o.x+mod)%mod; }
//     H operator*(H o) { return ll(x)*o.x%mod; }
//     int get() const { return x; }
//     bool operator==(H o) const { return get() == o.get(); }
//     // bool operator<(H o) const { return get() < o.get(); }
// };

typedef uint64_t ull;
struct H{
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull) (m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

H hashString(vi& s) { H h{}; for(auto c : s) h = h*C+(c+1); return h; }


struct HashInterval {
    vector<H> ha, pw;
    HashInterval(vi& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,0,sz(str))
            ha[i+1] = ha[i] * C + (str[i]+1), pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b-a];
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, q; cin >> n >> m >> q;
    vii moves(m);
    rep(i, 0, m) {
        cin >> moves[i].f >> moves[i].s; moves[i].f--, moves[i].s--;
    }
    if(n > 1000) {
        // average moves of each element is small
        vi a(n);
        iota(all(a), 0);
        map<pii, vii> loc;
        rep(i, 0, n-1) {
            loc[{a[i], a[i+1]}].push_back({0, n+5});
        }
        rep(i, 0, m) {
            auto [l,r] = moves[i];
            for(int v : {l, r}) {
                rep(idx, max(0, v-1), min(n-2, v)+1){
                    loc[{a[idx], a[idx+1]}].back().second = i+1;
                }
            }
            swap(a[l], a[r]);
            for(int v : {l, r}) {
                rep(idx, max(0, v-1), min(n-2, v)+1){
                    loc[{a[idx], a[idx+1]}].push_back({i+1, n+5});
                }
            }
        }
        rep(qid, 0, q) {
            int k; cin >> k;
            vi b(k);
            int ans = n+5;
            vii events;
            rep(i, 0, k) {
                cin >> b[i]; 
                b[i]--;
            }
            if(k == 1) {
                cout << 0 << "\n";
                continue;
            }
            rep(i, 0, k-1){
                for(auto [l, r] : loc[{b[i], b[i+1]}]){
                    events.push_back({l, 1});
                    events.push_back({r, -1});
                }
            }
            sort(all(events));
            int cover = 0;
            for(auto [t, dc] : events) {
                cover += dc;
                if(cover == k-1) {
                    ans = min(ans, t);
                }
            }
            cout << ans << "\n";
        }
    } else {
        vi a(n);
        iota(all(a), 0);
        vvi at;
        vector<HashInterval> hashes;
        at.push_back(a);
        hashes.push_back(a);
        for(auto [l, r] : moves) {
            vi v = at.back();
            v[a[l]] = r;
            v[a[r]] = l;
            swap(a[l], a[r]);
            at.push_back(v);
            hashes.push_back(a);
        }
        rep(qid, 0, q) {
            int k; cin >> k;
            vi b(k);
            rep(i, 0, k) {
                cin >> b[i]; b[i]--;
            }
            H target = hashString(b);
            int ans = n+5;
            rep(t, 0, sz(hashes)) {
                int s = at[t][b[0]];
                if(s + k > n) continue;
                H sub = hashes[t].hashInterval(s, s+k);
                if(sub == target) {
                    ans = min(ans, t);
                    break;
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
