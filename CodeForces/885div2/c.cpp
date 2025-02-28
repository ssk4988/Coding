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
        int n; cin >> n;
        bool dull = true;
        vi a(n), b(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        rep(i, 0, n) cin >> b[i];
        vi cnt(3);
        rep(i, 0, n) {
            int u = a[i], v = b[i];
            int ops = 0;
            while(u && v) {
                int did = (max(u,v) / min(u,v));
                if(did > 6) {
                    if(u>=v){
                        u %= 4*v;
                    } else {
                        v %= 4*u;
                    }
                    continue;
                }
                int w = abs(u-v);
                ops++;
                u = v;
                v = w;
            }
            if(!u && !v) continue;
            if(!v) ops += 1;
            cnt[ops%3] = 1;
        }
        cout << (cnt[0]+cnt[1]+cnt[2]>1 ?"NO":"YES") << "\n";
    }
    
    return 0;
}
