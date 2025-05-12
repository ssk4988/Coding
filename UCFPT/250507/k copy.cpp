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

vi pi(const string& s) {
    vi p(sz(s));
    rep(i,1,sz(s)) {
        int g = p[i-1];
        while(g && s[i] != s[g]) g = p[g-1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

struct FT {
    vector<ll> s;
    FT(int n)  : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if(sum <= 0) return -1;
        int pos = 0;
        for(int pw = 1 << 25; pw; pw >>= 1) {
            if(pos + pw <= sz(s) && s[pos + pw-1] < sum) pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    FT ft(q+10);
    int last = 0;
    string s;
    vi p;
    rep(qid, 0, q) {
        string t; cin >> t;
        if(t == "add") {
            char v; cin >> v;
            char c = ((v - 'a' + last) % 26) + 'a';
            s.push_back(c);
            if(sz(s) == 1) {
                p.push_back(0);
            } else {
                int i = sz(s) - 1;
                int g = p[i-1];
                while(g && s[i] != s[g]) g = p[g-1];
                p.push_back(g + (s[i] == s[g]));
            }
            ft.update(p.back(), 1);
            cerr << s << endl;
            for(int v : p) cerr << v << " ";
            cerr << endl;
        } else {
            int n = sz(s);
            int k; cin >> k;
            k = (k-1 + last + n) % n + 1;
            int ans = ft.query(q+10) - ft.query(k);
            ans++;
            last = ans;
            cout << ans << "\n";
        }
    }
    return 0;
}
