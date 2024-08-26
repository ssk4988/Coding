#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    pii bon, cly, tar;
    rep(i, 0, r)
    {
        cin >> grid[i];
        rep(j, 0, c)
        {
            if (grid[i][j] == 'B')
                bon = {i, j};
            else if (grid[i][j] == 'C')
                cly = {i, j};
            else if (grid[i][j] == 'F')
                tar = {i, j};
            // else
        }
    }
    vii dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int ans = 1e9;
    int moves = 0;
    auto bt = [&](int br, int bc, int cr, int cc, auto &&bt) -> void
    {
        // if(pii{br, bc} == tar){
        //     br = -1, bc = -1;
        // }
        // if(pii{})
        // cout << br << " " << bc << " " << cr << " " << cc << " " << moves << endl;
        if (pii{br, bc} == tar && pii{cr, cc} == tar)
        {
            ans = min(ans, moves);
            return;
        }
        vii posb;
        int addb = 0, addc = 0;
        if (pii{br, bc} == tar)
        {
            posb.push_back(tar);
        }
        else
        {
            addb = 1;
            for (auto [dr, dc] : dir)
            {
                int br1 = br + dr, bc1 = bc + dc;
                if(br1 < 0 || br1 >= r || bc1 < 0 || bc1 >= c) continue;
                // cout << br1 << " " << bc1 << " " << r << " " << c << endl;
                if(grid[br1][bc1] != '.' && pii{br1, bc1} != tar) continue;
                posb.push_back({br1, bc1});
            }
        }
        // cout << "posb" << endl;
        vii posc;
        if (pii{cr, cc} == tar)
        {
            posc.push_back(tar);
        }
        else
        {
            addc = 1;
        }
        for(auto [br1, bc1] : posb){
            bool block = pii{br1, bc1} != tar;
            if(block) grid[br1][bc1] = 'x';
            for (auto [dr, dc] : dir)
            {
                int cr1 = cr + dr, cc1 = cc + dc;
                if(cr1 < 0 || cr1 >= r || cc1 < 0 || cc1 >= c) continue;
                if(grid[cr1][cc1] != '.' && pii{cr1, cc1} != tar) continue;
                moves += addb + addc;
                bool block1 = pii{cr1, cc1} != tar;
                if(block1) grid[cr1][cc1] = 'x';
                bt(br1, bc1, cr1, cc1, bt);
                if(block1) grid[cr1][cc1] = '.';
                moves -= addb + addc;
            }
            if(!addc) {
                moves += addb;
                bt(br1, bc1, cr, cc, bt);
                moves -= addb;
            }
            // for(auto [cr1, cc1] : posc) {
            // }
            if(block) grid[br1][bc1] = '.';
        }
    };
    bt(bon.first, bon.second, cly.first, cly.second, bt);
    if (ans == 1e9)
        cout << -1 << "\n";
    else
        cout << ans << "\n";

    return 0;
}
