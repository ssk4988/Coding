#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vii p(n*m), d(n*m);
    vvi g(n, vi(m));
    rep(i, 0, n){
        rep(j, 0, m){
            cin >> g[i][j]; g[i][j]--;
            p[g[i][j]] = {i, j};
        }
    }
    rep(i, 0, n){
        rep(j, 0, m){
            int v; cin >> v; v--;
            d[v] = {i, j};
        }
    }
    vector<array<int, 4>> x;
    auto sw = [&](int a, int b, int c, int d) {
        if((b == 0 || g[a][b-1] < g[c][d]) && (b + 1 == m || g[a][b+1] > g[c][d])
        && (d == 0 || g[c][d-1] < g[a][b]) && (d+1 == m || g[c][d+1] > g[a][b])) {
            swap(g[a][b], g[c][d]);
            swap(p[g[a][b]], p[g[c][d]]);
            x.push_back({a, b, c, d});
            return true;
        }
        return false;
    };
    auto mv = [&](int a, int b, int c, int d) {
        rep(i, 0, b+1){
            if(sw(a, b, c, d)) break;
            if(g[a][i] > g[c][d]) sw(a, i, c, d);
        }
    };
    for(int i = n*m-1; i >= 0; i--){
        if(p[i] == d[i]) continue;
        mv(p[i].first, p[i].second, d[i].first, d[i].second);
    }
    cout << x.size() << "\n";
    for(auto [a, b, c, d] : x){
        cout << a+1 << " " << b+1 << " " << c+1 << " " << d+1 << "\n";
    }
    return 0;
}
