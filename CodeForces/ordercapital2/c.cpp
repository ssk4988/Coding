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
/*
3 2 1
3 1 3
1 4 3
1 3 7

3 2 1
2 5 1
2 1 6
1 3 6

6 5 4
5 11 4
5 4 15
4 9 15

6 5 4
6 4 9
4 10 9
4 9 19

min slides left and adds to all on left of it

inversions on left of min should be fixed first



3 2 4 2

3 2 4 2
3 2 2 6
2 5 2 6
2 2 7 6
2 2 6 13

3 2 4 2
2 5 4 2
2 4 9 2
2 4 2 11
2 2 6 11



1 4 3 2 3 2 5
1 3 2 3 2 14 5
1 2 2 7 5 14 5
1 2 2 5 14 14 5
1 2 2 5 5 19 19

1 4 3 2 3 2 5
1 3 7 2 3 2 5
1 2 5 9 3 2 5
1 2 3 8 12 2 5
1 2 2 5 10 14 5
1 2 2 5 5 15 19





6 2 5 1 4 3
*/
struct UF {
    vi e;
    vl sm, mx;
    UF(int n) : e(n, -1), sm(n), mx(n) {}
    int find(int u) { return e[u] < 0 ? u : e[u] = find(e[u]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v]; e[v] = u;
        sm[u] += sm[v];
        mx[u] = max(mx[u], mx[v]);
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        UF uf(n);
        rep(i, 0, n) {
            cin >> a[i];
            uf.sm[i] = a[i];
            uf.mx[i] = i;
        }
        ll ans = 0;
        for(int i = n-1; i >= 0; i--) {
            while(uf.find(i) != uf.find(n-1) && uf.sm[uf.find(i)] > a[uf.mx[uf.find(i)]+1]) {
                uf.join(i, uf.mx[uf.find(i)]+1);
            }
            if(uf.find(i) == uf.find(n-1)) ans = max(ans, uf.sm[uf.find(i)]);
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
