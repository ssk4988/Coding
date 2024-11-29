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

struct UF {
    vi e;
    UF(int n) : e(n, -1){}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi x(n), y(n), r(n);
    rep(i, 0, n) {
        cin >> x[i] >> y[i] >> r[i];
    }
    UF uf(n);
    double ans = 0;
    vector<tuple<double, int, int>> edges;
    rep(i,0,n){
        rep(j, 0, i){
            edges.push_back({hypot(x[i] - x[j], y[i] - y[j]) - r[i] - r[j], i, j});
        }
    }
    sort(all(edges));
    for(auto [w, i, j] : edges){
        if(uf.join(i,j)) ans += w;
    }
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
