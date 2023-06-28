#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;

struct UF {
    vl e;
    ll ans = 0;
    UF(int n) : e(n, -1), ans(0){}
    ll size(int x) {return -e[find(x)];}
    int find(int x){return e[x] < 0 ? x : find(e[x]); }
    bool join(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        if(size(a) > 1){
            ans -= ll(size(a)) * (size(a) - 1) / 2;
        }
        if(size(b) > 1){
            ans -= ll(size(b)) * (size(b) - 1) / 2;
        }
        // ans -= ll(size(a)) * (size(a));
        // ans -= ll(size(b)) * (size(b));
        e[a] += e[b]; e[b] = a;
        if(size(a) > 1){
            ans += ll(size(a)) * (size(a) - 1) / 2;
        }
        // ans += ll(size(a)) * (size(a));
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, q; cin >> n >> m >> q;
        vector<array<int, 3>> rs(m);
        rep(i, 0, m){
            cin >> rs[i][1] >> rs[i][2] >> rs[i][0];
            rs[i][1]--,rs[i][2]--;
        }
        sort(all(rs));
        reverse(all(rs));
        vl anss(q, -1);
        vpi qs(q);
        rep(i, 0, q){
            cin >> qs[i].f;
            qs[i].s = i;
        }
        sort(all(qs));
        reverse(all(qs));
        int pnter = 0;
        UF uf(n);
        rep(i, 0, q){
            auto [w, idx] = qs[i];
            while(pnter < m && rs[pnter][0] >= w){
                uf.join(rs[pnter][1], rs[pnter][2]);
                pnter++;
            }
            anss[idx] = uf.ans;
        }
        rep(i, 0, q){
            cout << anss[i] << "\n";
        }
    }
}
