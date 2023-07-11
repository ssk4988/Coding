#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using vvl = vector<vl>;

int mdist(int i1, int j1, int i2, int j2){
    return abs(i1 - i2) + abs(j1 - j2);
}
using a3 = array<ll, 3>;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    vvi grid(r + 2, vi(c + 2));
    int startr, startc, destr, destc;
    rep(i, 0, r){
        string str; cin >> str;
        rep(j, 0, c){
            if(str[j] == '#'){
                grid[i + 1][j + 1] = 0; // wall
            }
            if(str[j] == '.'){
                grid[i + 1][j + 1] = 1; // empty
            }
            if(str[j] == 'S'){
                grid[i + 1][j + 1] = 1;
                startr = i + 1, startc = j + 1;
            }
            if(str[j] == 'C'){
                grid[i + 1][j + 1] = 1;
                destr = i + 1, destc = j + 1;
            }
        }
    }
    r += 2, c += 2;
    vector<vvi> walldist(r, vvi(c, vi(4)));
    vector<vvpi> edges(r, vvpi(c));
    // inc row
    rep(j, 0, c){
        int pre = 0;
        int pv = -1;
        rep(i, 0, r){
            if(pv != -1) edges[i][j].pb({pv, j});
            walldist[i][j][0] = pre;
            pre++;
            if(pre == 1) pv = i;
            if(grid[i][j] == 0){
                pre = 0;
                pv = -1;
            }
        }
    }
    // dec row
    rep(j, 0, c){
        int pre = 0;
        int pv = -1;
        for(int i = r - 1; i >= 0; i--){
            if(pv != -1) edges[i][j].pb({pv, j});
            walldist[i][j][1] = pre;
            pre++;
            if(pre == 1) pv = i;
            if(grid[i][j] == 0){
                pre = 0;
                pv = -1;
            }
        }
    }
    // inc col
    rep(i, 0, r){
        int pre = 0;
        int pv = -1;
        rep(j, 0, c){
            if(pv != -1) edges[i][j].pb({i, pv});
            walldist[i][j][2] = pre;
            pre++;
            if(pre == 1) pv = j;
            if(grid[i][j] == 0){
                pre = 0;
                pv = -1;
            }
        }
    }
    // dec col
    rep(i, 0, r){
        int pre = 0;
        int pv = -1;
        for(int j = c - 1; j >= 0; j--){
            if(pv != -1) edges[i][j].pb({i, pv});
            walldist[i][j][3] = pre;
            pre++;
            if(pre == 1) pv = j;
            if(grid[i][j] == 0){
                pre = 0;
                pv = -1;
            }
        }
    }
    vvi wd(r, vi(c, INT_MAX));
    rep(i, 0, r){
        rep(j, 0, c){
            rep(k, 0, 4){
                wd[i][j] = min(wd[i][j], walldist[i][j][k]);
            }
        }
    }
    rep(i, 1, r - 1){
        rep(j, 1, c - 1){
            if(grid[i][j]){
                if(grid[i-1][j]) edges[i][j].pb({i-1, j});
                if(grid[i+1][j]) edges[i][j].pb({i+1, j});
                if(grid[i][j+1]) edges[i][j].pb({i, j+1});
                if(grid[i][j-1]) edges[i][j].pb({i, j-1});
            }
        }
    }
    vvl dist(r, vl(c, 1'000'000'000'000LL));
    vvi visited(r, vi(c));
    dist[startr][startc] = 0;
    priority_queue<a3, vector<a3>, greater<a3>> pq;
    pq.push({0, startr, startc});
    while(!pq.empty()){
        auto [d, i, j] = pq.top();pq.pop();
        if(visited[i][j]) continue;
        visited[i][j] = true;
        for(auto [i1, j1] : edges[i][j]){
            ll w = 1 + (mdist(i, j, i1, j1) > 1 ? wd[i][j] : 0);
            if(!visited[i1][j1] && w + d < dist[i1][j1]){
                dist[i1][j1] = w + d;
                pq.push({dist[i1][j1], i1, j1});
            }
        }
    }
    cout << dist[destr][destc] << "\n";

    return 0;
}