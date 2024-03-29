#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

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
};

H addHash(H h, char c){
    return h * C + c;
}

template <class F> struct centroid {
    vector<vector<int>> adj;
    F f;
    vector<int> sub_sz;
    centroid(const vector<vector<int>>& a_adj, F a_f)
        : adj(a_adj), f(a_f), sub_sz(sz(adj), -1) {
        for (int i = 0; i < sz(adj); i++)
            if (sub_sz[i] == -1) dfs(i);
    }
    void calc_sz(int u, int p) {
        sub_sz[u] = 1;
        for (int v : adj[u])
            if (v != p)
                calc_sz(v, u), sub_sz[u] += sub_sz[v];
    }
    void dfs(int u) {
        calc_sz(u, -1);
        for (int p = -1, sz_root = sub_sz[u];;) {
            auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) {
                return v != p && 2 * sub_sz[v] > sz_root;
            });
            if (big_ch == end(adj[u])) break;
            p = u, u = *big_ch;
        }
        f(adj, u);
        for (int v : adj[u]) {
            iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
            adj[v].pop_back();
            dfs(v);
        }
    }
};

bool open(char c){
    return c== '(' || c == '[' || c == '{';
}

char invert(char c){
    if(c == '(') return ')';
    if(c == '{') return '}';
    if(c == '[') return ']';
    if(c == ')') return '(';
    if(c == '}') return '{';
    if(c == ']') return '[';
    return -1;
}

char rev(char c){
    if(c == '(') return ')';
    if(c == '{') return '}';
    if(c == '[') return ']';
    return -1;
}

// ()()()((([)]))))

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string str; cin >> str;
    vvi adj(n);
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    ll ans = 0;
    auto sub = [&](vvi &g, int root) -> void {
        cout << "root: " << root << endl;
        vector<H> hst;
        vector<char> st;
        map<H, ll> freq, freq1;
        vector<map<H, ll>> treefreq, treefreq1;
        int badcnt = 0; // counts opens
        auto addst = [&](char c) -> void {
            hst.push_back(addHash((sz(hst) ? hst.back() : 0), c));
            st.push_back(c);
            badcnt += open(st.back());
        };
        auto popst = [&]() -> void {
            badcnt -= open(st.back());
            st.pop_back();
            hst.pop_back();
        };
        auto printst = [&]() -> void {
            for(char c : st) cout << c;
        };
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            bool rem = false;
            if(sz(st) && !open(str[u]) && invert(st.back()) == str[u]){
                rem = true;
                // matched a close with an open
                popst();
            }
            else{
                addst(str[u]);
            }
            cout << "dfsing on " << u << " with open=" << badcnt << " and st= ";
            printst();
            cout << endl;
            // cout << " and hash=" << hst.back().get() << endl;
            // if(badcnt == 0) {
                freq[hst.back()]++;
                treefreq.back()[hst.back()]++;
            // }
            for(int v : g[u]){
                if(v == p) continue;
                dfs(v, u, dfs);
            }
            if(rem){
                addst(invert(str[u]));
            }
            else popst();
        };
        // add 0 to hst
        hst.push_back(0);
        for(int v : g[root]){
            treefreq.push_back({});
            dfs(v, root, dfs);
        }
        freq[0]++;
        cout << "now doing with centroid" << endl;
        swap(freq, freq1);
        swap(treefreq, treefreq1);
        // hst.pop_back();
        // cout << "stack leftover: ";
        // printst();
        // cout << endl;
        // cout << "inversion: ";
        rep(i, 0, n){
            str[i] = invert(str[i]);
            // cout << str[i];
        }
        // cout << endl;
        addst(str[root]);
        for(int v : g[root]){
            treefreq.push_back({});
            dfs(v, root, dfs);
        }
        // dfs(root, -1, dfs);
        for(auto [key, val] : freq){
            cout << key.get() << " " << val << " " << freq1[key] << endl;
            ans += val * freq1[key];
        }
        rep(i, 0, sz(treefreq)){
            for(auto [key, val] : treefreq[i]){
                ans -= val * treefreq1[i][key];
            }
        }
        rep(i, 0, n){
            str[i] = invert(str[i]);
        }
    };

    centroid(adj, sub);
    cout << ans << "\n";


    
    
    return 0;
}
