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

vi max_plus(const vi &convex,
            const vi arbitrary)
{
    int n = ssize(convex);
    int m = ssize(arbitrary);
    vi res(n + m - 1, INT_MIN);
    auto dnc = [&](auto &&self, int res_le, int res_ri,
                   int arb_le, int arb_ri) -> void
    {
        if (res_le >= res_ri)
            return;
        int mid_res = (res_le + res_ri) / 2;
        int op_arb = arb_le;
        for (int i = arb_le; i < min(mid_res + 1, arb_ri);
             i++)
        {
            int j = mid_res - i;
            if (j >= n)
                continue;
            if (res[mid_res] < convex[j] + arbitrary[i])
            {
                res[mid_res] = convex[j] + arbitrary[i];
                op_arb = i;
            }
        }
        self(self, res_le, mid_res, arb_le,
             min(arb_ri, op_arb + 1));
        self(self, mid_res + 1, res_ri, op_arb, arb_ri);
    };
    dnc(dnc, 0, n + m - 1, 0, m);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t;
    cin >> t;
    int c; cin >> c;
    int n; cin >> n;
    vl by(n);
    vi inc;
    inc.pb(0);
    rep(i, 0, n) {
        cin >> by[i];
    }
    while(inc.back() < t) {
        inc.push_back(inc.back() + by[(sz(inc)-1) % sz(by)]);
    }
    while(sz(inc) && inc.back() > t) inc.pop_back();
    // rep(i, 0, sz(inc)){
    //     cerr << i << " " << inc[i] << endl;
    // }
    {
        vi inc2(t+1);
        rep(i, 0, sz(inc)) {
            inc2[inc[i]] = 2 * i;
        }
        rep(i, 1, sz(inc2)) {
            inc2[i] = max(inc2[i], inc2[i-1]);
        }
        inc = inc2;
    }
    // inc[i] = min time to get defense of i
    int b, m; cin >> b >> m;
    vi convex;
    convex.pb(b);
    vl dif(m);
    rep(i, 0, m) {
        cin >> dif[i];
    }
    int last = b;
    while(convex.back() < t) {
        last += dif[(sz(convex)-1)%sz(dif)];
        convex.pb(convex.back() + last);
    }
    while(sz(convex) && convex.back() > t) convex.pop_back();
    // cerr << "pre: " << endl;
    // rep(i, 0, sz(convex)) cerr << i << " " << convex[i] << endl;
    convex.insert(begin(convex), 0);
    {
        vi convex2(t + 1);
        rep(i, 0, sz(convex)) {
            convex2[convex[i]] = i * 3;
        }
        rep(i, 1, sz(convex2)) {
            convex2[i] = max(convex2[i], convex2[i-1]);
        }
        convex = convex2;
    }
    // rep(i, 0, sz(convex)) {
    //     cout << i << " " << convex[i] << "\n";
    // }
    // convex[i] = min time to get defense of i
    
    vi res = max_plus(convex, inc);
    // res = time of i, defense
    // cerr << "res" << endl;
    // rep(i, 0, sz(res)) {
    //     cerr << i << " " << res[i] << endl;
    // }
    rep(i, 0, sz(res)) {
        if(i) res[i] = max(res[i], res[i-1]);
        if(i+c < sz(res)) {
            res[i+c] = max(res[i+c], res[i]+1);
        }
        // cerr << i << " " << res[i] << endl;
    }
    cout << res[t] << "\n";

    return 0;
}
