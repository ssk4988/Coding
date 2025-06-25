#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

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

vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    int C = 1e5+10;
    int R = 51;
    int N = R * C;
    UF uf(N);
    vector<set<int>> rows(R);
    rep(i, 0, C) {
        rep(j, 0, R) {
            rows[j].insert(i);
        }
    }
    rep(qid, 0, q) {
        int t; cin >> t;
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2; r1--, c1--, r2--, c2--;
        if(t == 0) {
            if(r1 > r2) swap(r1, r2);
            if(c1 > c2) swap(c1, c2);
            rep(r, r1, r2+1) {
                while(true) {
                    auto it = rows[r].lower_bound(c1);
                    if(it == end(rows[r])) break;
                    auto c = *it;
                    if(c <= c2) {
                        rows[r].erase(it);
                        rep(i, 0, 4) {
                            int r3 = r + dr[i], c3 = c + dc[i];
                            if(min(r3, c3) < 0 || r3 >= R || c3 >= C) continue;
                            if(!rows[r3].count(c3)) {
                                uf.join(r3*C+c3, r*C+c);
                            }
                        }
                    } else break;
                }
            }
        } else {
            cout << (!rows[r1].count(c1) && !rows[r2].count(c2) && uf.find(r1*C+c1) == uf.find(r2*C+c2)) << "\n";
        }
    }

    return 0;
}
