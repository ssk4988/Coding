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


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    vector<string> grid(r);
    rep(i, 0, r){
        cin >> grid[i];
    }
    vii cluepos;
    vii clues;
    rep(i, 0, r){
        rep(j, 0, c){
            if(grid[i][j] == '#') continue;
            if(j == 0 || grid[i][j-1] == '#' || i == 0 || grid[i-1][j] == '#'){
                cluepos.push_back({i, j});
            }
            if(j == 0 || grid[i][j-1] == '#') clues.push_back({sz(cluepos) - 1, 0});
            if(i == 0 || grid[i-1][j] == '#') clues.push_back({sz(cluepos) - 1, 1});
        }
    }
    // for(auto [cluenum, t] : clues){
    //     cout << (cluenum + 1) << (t ? "D" : "A") << " " << cluepos[cluenum].f << "," << cluepos[cluenum].s << "\n";
    // }
    vii dirs = {{0, 1}, {1, 0}};
    vi ans;
    while(true){
        bool emp = false;
        rep(i, 0, r){
            rep(j, 0, c){
                if(grid[i][j] == '.') emp = true;
            }
        }
        if(!emp) break;
        vector<tuple<int, int, int>> order;
        rep(x, 0, sz(clues)){
            auto [cluenum, t] = clues[x];
            auto dir = dirs[t];
            int num = 0, denom = 0, cnt = 0, filled = 0;
            auto [i, j] = cluepos[cluenum];
            while(i < r && j < c && grid[i][j] != '#'){
                filled += grid[i][j] != '.';
                num += filled;
                cnt++;
                denom += cnt;
                // cout << i << "," << j << " " << grid[i][j] << "\n";
                tie(i, j) = pii{i, j} + dir;
            }
            if(num == denom) continue;
            // cout << (cluenum + 1) << (t ? "D" : "A") << " " << num << "/" << denom << "\n";
            order.push_back({x, num, denom});
        }
        sort(all(order), [&](auto o1, auto o2) -> bool {
            auto [x1, num1, denom1] = o1;
            auto [x2, num2, denom2] = o2;
            if(num1 * denom2 != num2 * denom1) return num1 * denom2 > num2 * denom1;
            auto [cn1, t1] = clues[x1];
            auto [cn2, t2] = clues[x2];
            if(t1 != t2) return t1 < t2;
            return cn1 < cn2;
        });
        auto [x, num, denom] = order[0];
        auto [cluenum, t] = clues[x];
        auto dir = dirs[t];
        auto [i, j] = cluepos[cluenum];
        while(i < r && j < c && grid[i][j] != '#'){
            grid[i][j] = 'A';
            tie(i, j) = pii{i, j} + dir;
        }
        ans.push_back(x);
    }
    for(auto x : ans){
        auto [cluenum, t] = clues[x];
        cout << (cluenum + 1) << (t ? "D" : "A") << "\n";
    }

    return 0;
}