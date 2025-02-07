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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, q; cin >> n >> q;
        vi p(n);
        rep(i, 0, n) {
            cin >> p[i]; p[i]--;
        }
        vi isreq(n-1);
        {
            int l = 0;
            while(l < n) {
                int r = l;
                set<int> c;
                while(r == l || *c.rbegin() != r-1) {
                    c.insert(p[r++]);
                }
                rep(i, l, r-1) {
                    isreq[i] = true;
                }
                l = r;
            }
        }
        string s; cin >> s;
        vi cover(n-1);
        rep(i, 0, n) {
            if(s[i] == 'L') cover[i-1]++;
            else cover[i]++;
        }
        int need = accumulate(all(isreq), 0);
        int cur = 0;
        rep(i, 0, n-1) if(cover[i] && isreq[i]) cur++;
        rep(i, 0, q) {
            int x; cin >> x; x--;
            int dec = s[x] == 'L' ? x-1 : x;
            if(cover[dec] == 1 && isreq[dec]) cur--;
            cover[dec]--;
            s[x] = (s[x] == 'L' ? 'R' : 'L');
            int inc = s[x] == 'L' ? x-1 : x;
            if(cover[inc] == 0 && isreq[inc]) cur++;
            cover[inc]++;
            cout << (need == cur ? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}
