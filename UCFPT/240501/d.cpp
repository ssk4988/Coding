#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

// #pragma GCC optimize("Ofast")
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;


struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) {
        return e[x] < 0 ? x : e[x] = find(e[x]);
    }
    bool join(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};


const int LIM = 1000100;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vi lp(LIM+1), primes;
    rep(i, 2, LIM+1) {
        if(lp[i] == 0) primes.push_back(lp[i] = i);
        for(int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j)
            lp[i * primes[j]] = primes[j];
    }
    vvi pfs(LIM);
    vi lbl(LIM);
    rep(i, 1, LIM){
        int cur = i;
        while(cur > 1){
            int p = lp[cur];
            if(sz(pfs[i]) == 0 || pfs[i].back() != p) pfs[i].push_back(p);
            cur /= p;
        }
        lbl[i] = 1;
        for(int p : pfs[i]) lbl[i] *= p;
    }
    vvi sub(LIM);
    rep(i, 1, LIM){
        if(sz(sub[lbl[i]])) continue;
        int c = sz(pfs[i]);
        rep(mask, 0, (1 << c) - 1){
            int m = 1;
            rep(j, 0, c){
                if((mask >> j) & 1) m *= pfs[i][j];
            }
            sub[lbl[i]].push_back(lbl[m]);
        }
    }
    int nc; cin >> nc;
    vvi m(LIM);
    rep(cn, 0, nc){
        int l, r; cin >> l >> r;
        int n = r - l + 1;
        vi a(n);
        vi used;
        // map<int, vi> m;
        int pp = -1; // index of prime power
        rep(i, 0, n){
            a[i] = l + i;
            m[lbl[a[i]]].push_back(i);
            used.push_back(lbl[a[i]]);
            if(sz(pfs[a[i]]) == 1) pp = i;
        }
        sort(all(used));
        used.erase(unique(all(used)), used.end());
        vector<vector<array<int, 3>>> adj(100);
        auto add = [&](int x, int y)-> void {
            int x1 = 0, y1 = 0, c = 0;
            while(x1 < sz(pfs[a[x]]) && y1 < sz(pfs[a[y]])){
                if(pfs[a[x]][x1] < pfs[a[y]][y1]){
                    x1++;
                } else if(pfs[a[x]][x1] == pfs[a[y]][y1]){
                    x1++, y1++;
                } else{
                    y1++;
                }
                c++;
            }
            c += sz(pfs[a[x]]) - x1;
            c += sz(pfs[a[y]]) - y1;
            adj[c].push_back({c, x, y});
            // set<int> s;
            // for(int p : pfs[a[x]]) s.insert(p);
            // for(int p : pfs[a[y]]) s.insert(p);
            // int c = sz(s);
        };
        if(a[0] == 1){
            rep(i, 0, n){
                add(0, i);
            }
        }
        else if(pp != -1){
            for(auto key : used){
                auto &val = m[key];
            // }
            // for(auto &[key, val] : m){
                // add same
                for(auto v : val){
                    add(val[0], v);
                }
                // add submask
                for(auto s : sub[key]){
                    if(sz(m[s])){
                        add(m[s][0], val[0]);
                        break;
                    }
                }
                // add prime power
                add(val[0], pp);
            }
        } else{
            // size is small
            rep(i, 0, n){
                rep(j, 0, n){
                    add(i, j);
                }
            }
        }
        int ans = 0;
        UF uf(n);
        // sort(all(adj));
        for(auto &v : adj){
            for(auto [c, i, j] : v){
                if(uf.join(i, j)) ans += c;
            }
        }
        // cout << sz(adj) << "\n";
        cout << ans << "\n";
        for(int key : used) m[key].clear();
    }

    return 0;
}
