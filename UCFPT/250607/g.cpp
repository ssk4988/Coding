#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, p, q; cin >> n >> p >> q;
    UF uf(n);
    rep(i, 0, p) {
        int u, v; cin >> u >> v; u--, v--;
        uf.join(u, v);
    }
    vi bad(n), weight(n);
    vii ed;
    rep(i, 0, q) {
        int u, v; cin >> u >> v; u--, v--;
        if(uf.find(u) == uf.find(v)) {
            bad[uf.find(u)] = 1;
        }
        ed.push_back({u, v});
    }
    rep(i, 0, n) {
        weight[uf.find(i)]++;
    }
    vi idxs;
    vi rl(n, -1);
    rep(i, 0, n) {
        if(weight[i] && !bad[i]) {
            rl[i] = sz(idxs);
            idxs.push_back(i);
        }
    }
    if(sz(idxs) == 0) {
        cout << "0 1\n";
        return 0;
    }
    if(sz(idxs) == 1) {
        cout << weight[idxs[0]] << " 1\n";
        return 0;
    }
    int g = sz(idxs);
    vvi can(g, vi(g, 1));
    for(auto [u, v] : ed) {
        u = uf.find(u), v = uf.find(v);
        if(rl[u] != -1 && rl[v] != -1) {
            assert(rl[u] != rl[v]);
            can[rl[u]][rl[v]] = 0;
            can[rl[v]][rl[u]] = 0;
        }
    }
    // rep(i, 0, n) {
        // cerr << i << " " << uf.find(i) << " " << bad[i] << " " << weight[i] << endl;
    // }
    {
        vi w(g);
        rep(i, 0, g) w[i] = weight[idxs[i]];
        weight = w;
    }
    // rep(i, 0, g) {
    //     rep(j, 0, g) {
            // cerr << can[i][j];
        // }
        // cerr << endl;
    // }
    int nl = g / 2, nr = g - g/2;
    vi ok(1 << nl, 1);
    rep(i, 0, nl) {
        rep(j, 0, nl) {
            if(!can[i][j]) {
                ok[(1 << i) | (1 << j)] = 0;
            }
        }
    }
    rep(b, 0, nl) {
        rep(mask, 0, 1 << nl) {
            if((mask >> b) & 1) {
                ok[mask] &= ok[mask ^ (1 << b)];
            }
        }
    }
    vii sos(1 << nl, pii{0, 0});
    rep(mask, 0, 1 << nl) {
        if(!ok[mask]) continue;
        sos[mask].second = 1;
        rep(i, 0, nl) {
            if((mask >> i)&1) {
                sos[mask].first += weight[i];
            }
        }
        // cerr << "before sum " << mask << " " << sos[mask].first << endl;
    }
    rep(b, 0, nl) {
        rep(mask, 0, 1 << nl) {
            if((mask >> b) & 1) {
                int mask1 = mask ^ (1 << b);
                if(sos[mask1].first > sos[mask].first) {
                    sos[mask] = sos[mask1];
                } else if(sos[mask1].first == sos[mask].first) {
                    sos[mask].second += sos[mask1].second;
                }
            }
        }
    }
    ok = vi(1 << nr, 1);
    pii ans{0, 0};
    rep(i, 0, nr) {
        rep(j, 0, nr) {
            if(!can[i+nl][j+nl]) {
                ok[(1 << i) | (1 << j)] = 0;
            }
        }
    }
    rep(b, 0, nr) {
        rep(mask, 0, 1 << nr) {
            if((mask >> b) & 1) {
                ok[mask] &= ok[mask ^ (1 << b)];
            }
        }
    }
    vi adj(nr);
    rep(i, 0, nr) {
        rep(j, 0, nl) {
            if(can[j][i+nl]) adj[i] |= 1 << j;
        }
    }
    rep(mask, 0, 1 << nr) {
        if(!ok[mask]) continue;
        int allow = (1 << nl)-1;
        int cw = 0;
        rep(b, 0, nr) {
            if((mask >> b)&1) {
                allow &= adj[b];
                cw += weight[nl+b];
            }
        }
        auto res = sos[allow];
        // cerr << "mask " << mask << " " << cw << " " << allow << " " << res.first << " " << res.second << endl;
        res.first += cw;
        if(res.first > ans.first) ans = res;
        else if(res.first == ans.first) ans.second += res.second;
    }
    cout << ans.first << " " << ans.second << "\n";



    return 0;
}
