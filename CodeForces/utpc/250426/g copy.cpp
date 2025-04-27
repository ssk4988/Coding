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

vl min_plus(const vl &convex,
            const vl arbitrary)
{
    int n = ssize(convex);
    int m = ssize(arbitrary);
    vl res(n + m - 1, LLONG_MIN);
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
    vl inc(n);
    rep(i, 0, n) {
        cin >> by[i];
        inc[i] = by[i];

        if(i) inc[i] += inc[i-1];
    }
    while(inc.back() < t) {
        inc.push_back(inc.back() + by[sz(inc) % sz(by)]);
    }
    inc.insert(begin(inc), 0);
    {
        vl inc2(sz(inc) * 2 + 1);
        rep(i, 0, sz(inc)) {
            inc2[2 * i] = inc[i];
        }
        rep(i, 1, sz(inc2)) {
            inc2[i] = max(inc2[i], inc2[i-1]);
        }
        inc = inc2;
    }
    rep(i, 0, sz(inc)){
        cerr << i << " " << inc[i] << endl;
    }
    // inc[i] = min time to get defense of i
    int b, m; cin >> b >> m;
    vl convex(m+1);
    convex[0] = b;
    vl dif(m);
    rep(i, 0, m) {
        cin >> dif[i];
        convex[i+1] = dif[i] + convex[i];
    }
    rep(_, 0, 10) {
        rep(i, 0, m) {
            convex.pb(convex.back() + dif[i]);
        }
    }
    convex.insert(begin(convex), 0);
    rep(i, 1, sz(convex)) convex[i] += convex[i-1];
    cout << "pre: " << endl;
    rep(i, 0, sz(convex)) cout << i << " " << convex[i] << endl;
    {
        vl convex2(sz(convex) * 3+ 1);
        rep(i, 0, sz(convex)) {
            convex2[i*3] = convex[i];
        }
        rep(i, 1, sz(convex2)) {
            convex2[i] = max(convex2[i], convex2[i-1]);
        }
        convex = convex2;
    }
    // rep(i, 0, sz(convex)) convex[i] *= 3;
    while(convex.back() > t) convex.pop_back();
    rep(i, 0, sz(convex)) {
        cout << i << " " << convex[i] << "\n";
    }
    // convex[i] = min time to get defense of i
    
    vl res = min_plus(convex, inc);
    // res = time of i, defense
    vi ans(t+1);
    cerr << "res" << endl;
    rep(i, 0, sz(res)) {
        cerr << i << " " << res[i] << endl;
        if(res[i] <= t) {
            ans[res[i]] = max(ans[res[i]], i);
        }
    }
    // cerr << "ans: " << endl;
    // rep(i, 0, sz(ans)) {
    //     if(i) ans[i] = max(ans[i], ans[i-1]);
    //     if(i+c < sz(ans)) {
    //         ans[i+1] = min(ans[i+1], ans[i]+c);
    //     }
    //     cerr << i << " " << ans[i] << endl;
    // }
    // cout << ans.back() << "\n";

    return 0;
}
