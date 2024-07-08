#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;

using bs = bitset<100>;

struct UF {
    vi e;
    vector<bs> test;
    vvi under;
    vi bad;
    UF(int n) : e(n, -1), test(n), under(n), bad(n) {
        rep(i, 0, n) {
            under[i].push_back(i);
            test[i][i] = 1;
        }
    }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        // if(sz(under[]))
        e[a] += e[b];
        e[b] = a;
        bad[a] = bad[a] | bad[b];
        test[a] |= test[b];
        for(int i : under[b]){
            under[a].push_back(i);
        }
        return true;
    }

};


void solve() {
    int n; cin >> n;
    UF uf(n);
    mt19937_64 rng(42069);
    vi perm(n);
    iota(all(perm), 0);
    shuffle(all(perm), rng);
    vi rev(n);
    rep(i, 0, n){
        rev[perm[i]] = i;
    }
    // i in my code is actually perm[i]
    rep(t, 0, 12){
        rep(i, 0, n){
            if(uf.find(i) != i) continue;
            // cout << i << " " << uf.test[i] << "\n";
        }
        vi p(n, -1);
        rep(i, 0, n){
            if(p[i] != -1) continue;
            int u = uf.find(i);
            rep(o, 0, n){
                int o2 = uf.find(o);
                if(uf.test[u][o] || p[o] != -1 || uf.bad[u] || uf.bad[o2]) continue;
                uf.test[u][o] = 1;
                uf.test[o2][i] = 1;
                p[i] = o;
                p[o] = i;
                break;
            }
            rep(o, 0, n){
                int o2 = uf.find(o);
                if(uf.test[u][o] || p[o] != -1 || p[i] != -1) continue;
                uf.test[u][o] = 1;
                uf.test[o2][i] = 1;
                p[i] = o;
                p[o] = i;
                break;
            }
        }
        cout << "test ";
        rep(i, 0, n){
            if(p[rev[i]] == -1) {
                cout << 0 << " ";
                continue;
            }
            cout << perm[p[rev[i]]]+1 << " ";
        }
        cout << endl;
        string str; cin >> str;
        rep(i,0,n){
            if(p[rev[i]] == -1) continue;
            int me = rev[i];
            int you = p[me];
            if(str[perm[me]] == '1' && str[perm[you]] == '1') {
                uf.join(me, p[me]);
            }
            else if(str[perm[me]] == '1' && str[perm[you]] == '0') {
                uf.bad[uf.find(me)] = 1;
            } 
            else if(str[perm[me]] == '0' && str[perm[you]] == '1') {
                uf.bad[uf.find(p[me])] = 1;
            } 
        }
    }
    bool found = false;
    rep(i, 0, n){
        int u = uf.find(i);
        if(sz(uf.under[u]) * 2 > n){
            found = true;
            vi ans(n);
            for(int x : uf.under[u]){
                ans[x] = 1; 
            }
            cout << "answer ";
            rep(i, 0,n) cout << ans[rev[i]];
            cout << endl;
            break;
        }
    }
    assert(found);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    return 0;
}
