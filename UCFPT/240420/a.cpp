#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define f first
#define s second

pii operator+(pii a, pii b){
    return {a.f + b.f, a.s + b.s};
}

pii operator-(pii a, pii b){
    return {a.f - b.f, a.s - b.s};
}

vii ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m));
    pii emp;
    rep(i, 0, n){
        rep(j, 0, m){
            cin >> grid[i][j];
            if(grid[i][j] == -1) emp = {i, j};
        }
    }
    pii tar;
    cin >> tar.f >> tar.s;
    tar.f--, tar.s--;
    // info: r, c, prev ind, prev dir
    vector<pair<pii, pii>> q;
    q.push_back({emp, {-1, -1}});
    int fidx = -1;
    for(int i = 0; i < sz(q); i++){
        auto [x, p] = q[i];
        auto [r, c] = x;
        if(x == tar) {
            fidx = i;
            break;
        }
        auto [preind, predir] = p;
        // cout << x.f << " " << x.s << " " << preind << " " << predir << "\n";
        vii moves; // car, dir
        rep(k, 0, sz(ds)){
            auto x1 = x + ds[k];
            auto x2 = x1 + ds[k];
            // cout << "try " << x2.f << " " << x2.s << "\n";
            if(x2.f < 0 || x2.f >= n || x2.s < 0 || x2.s >= m) continue;
            // cout << "check1\n";
            if(grid[x1.f][x1.s] != grid[x2.f][x2.s]) continue;
            // cout << "check2\n";
            if(grid[x2.f][x2.s] < -1) continue;
            // cout << "check3\n";
            moves.push_back({grid[x2.f][x2.s], k});
        }
        sort(all(moves));
        for(auto [car, move] : moves){
            q.push_back({x + ds[move] + ds[move], {i, move}});
        }
    }
    if(fidx == -1){
        cout << "impossible\n";
        return 0;
    }
    int idx = fidx;
    vi places;
    while(idx > 0){
        auto [x, p] = q[idx];
        auto [preind, predir] = p;
        places.push_back(grid[x.f][x.s]);
        idx = preind;
    }
    reverse(all(places));
    for(auto x : places){
        cout << x << " ";
    }
    cout << "\n";


    return 0;
}