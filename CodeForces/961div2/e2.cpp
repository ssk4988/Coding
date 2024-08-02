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
using vvl = vector<vl>;

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

using a2 = array<bool, 2>;
using a22 = array<array<bool, 2>, 2>;

struct Node {
    Node *l = 0, *r = 0;
    a22 val = a22{a2{0, 0}, a2{0, 0}};
    int lo, hi;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            comb();
        }
    }
    void comb() {
        rep(i, 0, 2){
            rep(j, 0, 2){
                val[i][j] = false;
                rep(k, 0, 2){
                    val[i][j] = val[i][j] || (l->val[i][k] && r->val[k][j]);
                }
            }
        }
    }
    void upd(int idx, int s1, int s2, bool v) {
        if(lo + 1 == hi) {
            val[s1][s2] = v;
            return;
        }
        int mid = lo + (hi - lo) / 2;
        if(mid <= idx) r->upd(idx, s1, s2, v);
        else l->upd(idx, s1, s2, v);
        comb();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n * 2);
        rep(i, 0, sz(a)){ 
            cin >> a[i];
        }
        if(n == 1) {
            cout << 0 << "\n";
            continue;
        }
        if(n % 2 == 0){
            ll mn = LLONG_MAX, mx = LLONG_MIN;
            for(int i = 0; i < n; i += 2){
                vl b = {a[i], a[i+1], a[n + i], a[n + i + 1]};
                vl c = {b[0] + b[1], b[2] + b[3]};
                vl d = {b[0] + b[3], b[1] + b[2]};
                sort(all(c));
                sort(all(d));
                if(c[0] < d[0]){
                    swap(c, d);
                }
                mn = min(mn, c[0]);
                mx = max(mx, c[1]);
            }
            cout << (mx - mn) << "\n";
            continue;
        }
        vl order;
        order.pb(a[0]);
        order.pb(a[n]);
        int cur = n ^ 1;
        while(cur != 0){
            order.pb(a[cur]);
            if(cur >= n) cur -= n;
            else cur += n;
            order.pb(a[cur]);
            cur ^= 1;
        }
        rotate(order.begin(), order.begin() + 1, order.end());
        Node tree(0, n);
        map<ll, vector<pair<int, pi>>> mpos;
        vl pos;
        for(int i = 0; i < sz(order); i += 2){
            vl p1 = {order[i], i == 0 ? order.back() : order[i - 1]};
            vl p2 = {order[i + 1], i + 2 == sz(order) ? order[0] : order[i + 2]};
            rep(s1, 0, 2){
                rep(s2, 0, 2){
                    mpos[p1[s1] + p2[s2]].push_back({i / 2, {s1, s2}});
                }
            }
        }
        for(auto &[key, val] : mpos){
            pos.pb(key);
        }
        auto works = [&]() -> bool {
            rep(i, 0, 2){
                if(tree.val[i][i]) return true;
            }
            return false;
        };
        int r = 0;
        ll ans = LLONG_MAX;
        rep(l, 0, sz(pos)){
            while(r < sz(pos) && !works()) {
                for(auto [idx, ss] : mpos[pos[r]]) {
                    auto [s1, s2] = ss;
                    tree.upd(idx, s1, s2, true);
                }
                r++;
            }
            if(works()) {
                ans = min(ans, pos[r - 1] - pos[l]);
            }
            for(auto [idx, ss] : mpos[pos[l]]) {
                auto [s1, s2] = ss;
                tree.upd(idx, s1, s2, false);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
