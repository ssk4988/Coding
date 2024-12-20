#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) x.size()

void solve() {
    int n; ll m; cin >> n >> m;
    vl w(n), l(n), r(n), c(n);
    rep(i, 0, n){
        cin >> w[i] >> l[i] >> r[i];
    }
    ll ans = 0;
    ll cur_ans = 0;
    {
        vi ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) { return w[i] > w[j]; });
        // rep(i, 0, n) cerr << ord[i] << " ";
        // cerr << endl;
        vl w2(n), r2(n), l2(n);
        rep(i, 0, n){
            w2[i] = w[ord[i]];
            r2[i] = r[ord[i]];
            l2[i] = l[ord[i]];
        }
        // reverse(all(w2));
        // assert(is_sorted(all(w2)));
        // reverse(all(w2));
        w = w2, r = r2, l = l2;
    }
    {
        ll left = m;
        rep(i, 0, n){
            cur_ans += w[i] * l[i];
            left -= l[i];
            c[i] = l[i];
        }
        rep(i, 0, n) {
            ll amt = min(r[i] - c[i], left);
            left -= amt;
            c[i] += amt;
            cur_ans += w[i] * amt;
        }
        ans = cur_ans;
    }
    // cerr << cur_ans << endl;
    vl add, rem, addw, remw;
    vl addp={0}, remp={0}, addwp={0}, remwp={0};
    rep(i, 0, n){
        add.push_back(r[i] - c[i]);
        addp.push_back(addp.back() + add.back());
        addw.push_back(add[i] * w[i]);
        addwp.push_back(addwp.back() + addw.back());
        rem.push_back(c[i] - l[i]);
        remp.push_back(remp.back() + rem.back());
        remw.push_back(rem[i] * w[i]);
        remwp.push_back(remwp.back() + remw.back());
        // cerr << i << " " << c[i] << " " << w[i] << " " << l[i] << " " << r[i] << " " << add[i] << " " << rem[i] << endl;
        // cerr << remwp[i] << endl;
    }
    rep(i, 0, n){
        // add as much as possible
        assert(remp[n]-remp[i+1] <= m - c[i]);
        if (remp[n]-remp[i+1] <= m - c[i]) {
            ll cand = cur_ans - (remwp[n] - remwp[i+1]) + w[i] * (remp[n]-remp[i+1]);
            ans = max(ans, cand);
        } 
        // remove as much as possible
        if(c[i] >= addp[i]) {
            ll cand = cur_ans - w[i] * addp[i] + addwp[i];
            ans = max(ans, cand);
        } else {
            // find max x such that add[0, x) <= c[i] on range [0, i)
            int x = upper_bound(all(addp), c[i]) - begin(addp);
            x--;
            ll ext = min(c[i] - addp[x], add[x]); // not actually required?
            ll cand = cur_ans + addwp[x] + w[x] * ext - w[i] * (ext + addp[x]);
            // int x = -1;
            // for(int dif = 1 << 20; dif; dif /= 2) {
            //     int cur = x + dif;
            //     if(cur >= i) continue;
            //     if(addp[x] <= c[i]) x = cur;
            // }
            // ll ext = min(add[x], c[i] - addp[x]);
            // ll cand = cur_ans + addwp[x] + w[x] * ext - w[i] * (ext + addp[x]);
            ans = max(ans, cand);
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    // int t; cin >> t;
    // while (t--) 
    solve();

    return 0;
}
