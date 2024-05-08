#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;

vi pi(const string& s) {
    vi p(sz(s));
    rep(i, 1, sz(s)) {
        int g = p[i - 1];
        while(g && s[i] != s[g]) g = p[g-1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

vi match(const string& s, const string& pat) {
    vi p = pi(pat + '\0' + s), res;
    rep(i, sz(p) - sz(s), sz(p))
        if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
    return res;
}

vi Z(string S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while(i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

void solve() {
    int n, q; cin >> n >> q;
    string s, t; cin >> s >> t;
    vl w(n);
    rep(i, 0, n) cin >> w[i];
    w.insert(w.begin(), 0);
    vl wsum(w);
    partial_sum(all(wsum), wsum.begin());
    vi kmp = pi(s);
    vl psum(n);
    rep(i, 0, n){
        psum[i] = w[i+1];
        if(kmp[i] > 0) psum[i] += psum[kmp[i] - 1];
    }
    partial_sum(all(psum), psum.begin());
    string comb = s + "\0" + t;
    vi z = Z(comb);
    z.erase(z.begin(), z.begin() + n);
    // rep(i, 0, n){
    //     cout << z[i] << " ";
    // }
    // cout << "\n";
    z.push_back(0);
    vector<vii> rbucket(n+1);
    vvi zbucket(n+1);
    vl zsum(n);
    rep(i, 0, n){
        zbucket[i + z[i]].push_back(i);
        zsum[i] = wsum[z[i]];
        if(i) zsum[i] += zsum[i-1];
    }
    zsum.insert(zsum.begin(), 0);
    vl ans(q);
    rep(i, 0, q){
        int l, r; cin >> l >> r; l--;
        rbucket[r].push_back({l, i});
    }
    set<int> inter;
    inter.insert(n);
    for(int r = n; r >= 0; r--){
        for(int i : zbucket[r]){
            inter.insert(i);
        }
        for(auto [l, i] : rbucket[r]){
            int x = *inter.lower_bound(l);
            // cout << "x for query " << i << " " << l << "," << r << " is " << x << "\n";
            ll res = zsum[x] - zsum[l] + (r == x ? 0 : psum[r - x - 1]);
            ans[i] = res;
        }
    }
    rep(i, 0, q){
        cout << ans[i] << "\n";
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    solve();

    return 0;
}
