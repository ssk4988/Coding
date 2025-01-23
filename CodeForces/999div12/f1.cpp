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
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vii stringify(string &s) {
    vii res;
    int l = 0;
    int n = sz(s);
    while(l < n) {
        int r = l;
        while(r < n && s[r] == s[l]) r++;
        res.pb({r-l, s[l]-'0'});
        l = r;
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        string s, t; cin >> s >> t;
        int n = sz(s);
        vii a = stringify(s), b = stringify(t);
        deque<pii> fs(all(a)), ft(all(b));
        int ans = 0;
        while(sz(fs) && sz(ft)) {
            if(fs[0] == ft[0]) {
                fs.pop_front();
                ft.pop_front();
                continue;
            }
            if(fs[0].s == ft[0].s) {
                if(fs[0] > ft[0] || sz(fs) <= 2) {
                    break;
                }
                vii buf;
                rep(i, 0, 4) {
                    if(sz(fs) == 0) break;
                    buf.pb(fs[0]);
                    fs.pop_front();
                }
                buf[0].f += buf[2].f;
                if(sz(buf) >= 4) buf[1].f += buf[3].f;
                fs.push_front(buf[1]);
                fs.push_front(buf[0]);
                ans++;
                continue;
            }
            if(sz(fs) < 2) break;
            vii buf;
            rep(i, 0, 3) {
                if(sz(fs) == 0) break;
                buf.pb(fs[0]);
                fs.pop_front();
            }
            if(sz(buf) >= 3) buf[0].f += buf[2].f;
            fs.push_front(buf[0]);
            fs.push_front(buf[1]);
            ans++;
        }
        if(sz(fs) || sz(ft)) {
            cout << "-1\n";
            continue;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
