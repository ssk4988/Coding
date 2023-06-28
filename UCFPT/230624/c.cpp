#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    vvi grid(r, vi(c));
    pi cottage, v;
    rep(i, 0, r){
        string str; cin >> str;
        rep(j, 0, c){
            if(str[j] == 'V'){
                v = {i, j};
            }
            if(str[j] == 'J') cottage = {i, j};
            if(str[j] == '+') grid[i][j] = 1;
        }
    }
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vvi mindist(r, vi(c, INT_MAX));
    vvi aux(r, vi(c, -1));
    rep(i, 0, r){
        rep(j, 0, c){
            if(i) aux[i][j] = max(aux[i][j], aux[i - 1][j]);
            if(j) aux[i][j] = max(aux[i][j], aux[i][j - 1]);
            if(grid[i][j]){
                aux[i][j] = max(aux[i][j], i + j);
            }
            if(aux[i][j] >= 0) mindist[i][j] = min(mindist[i][j], i + j - aux[i][j]);
        }
    }
    aux = vvi(r, vi(c, -1));
    for(int i = r - 1; i >= 0; i--){
        rep(j, 0, c){
            if(i + 1 < r) aux[i][j] = max(aux[i][j], aux[i + 1][j]);
            if(j) aux[i][j] = max(aux[i][j], aux[i][j - 1]);
            if(grid[i][j]){
                aux[i][j] = max(aux[i][j], (r - 1 - i) + j);
            }
            if(aux[i][j] >= 0) mindist[i][j] = min(mindist[i][j], (r - 1 - i) + j - aux[i][j]);
        }
    }
    aux = vvi(r, vi(c, -1));
    rep(i, 0, r){
        for(int j = c - 1; j >= 0; j--){
            if(i) aux[i][j] = max(aux[i][j], aux[i - 1][j]);
            if(j + 1 < c) aux[i][j] = max(aux[i][j], aux[i][j + 1]);
            if(grid[i][j]){
                aux[i][j] = max(aux[i][j], i + (c - 1 - j));
            }
            if(aux[i][j] >= 0) mindist[i][j] = min(mindist[i][j], i + (c - 1 - j) - aux[i][j]);
        }
    }
    aux = vvi(r, vi(c, -1));
    for(int i = r - 1; i >= 0; i--){
        for(int j = c - 1; j >= 0; j--){
            if(i + 1 < r) aux[i][j] = max(aux[i][j], aux[i + 1][j]);
            if(j + 1 < c) aux[i][j] = max(aux[i][j], aux[i][j + 1]);
            if(grid[i][j]){
                aux[i][j] = max(aux[i][j], (r - 1 - i) + (c - 1 - j));
            }
            if(aux[i][j] >= 0) mindist[i][j] = min(mindist[i][j], (r - 1 - i) + (c - 1 - j) - aux[i][j]);
        }
    }
    int lo = 0, hi = max(r, c);
    while(lo < hi){
        int mid = lo + (hi - lo + 1) / 2;
        vvi visited(r, vi(c));
        queue<pi> q;
        if(mindist[v.f][v.s] >= mid) q.push({v});
        while(q.size()){
            auto [i, j] = q.front();
            q.pop();
            if(visited[i][j]) continue;
            visited[i][j] = true;
            rep(k, 0, 4){
                int i1 = i + ds[k][0], j1 = j + ds[k][1];
                if(i1 >= 0 && i1 < r && j1 >= 0 && j1 < c && !visited[i1][j1] && mindist[i1][j1] >= mid){
                    q.push({i1, j1});
                }
            }
        }
        if(visited[cottage.f][cottage.s]){
            lo = mid;
        }else hi = mid - 1;
    }
    cout << lo << "\n";
}
