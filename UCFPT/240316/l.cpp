#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int k, n; cin >> k >> n;
    vector<vector<vi>> freq(4, vector<vi>(4));
    vi a(k), b(k);
    rep(i, 0, k){
        cin >> a[i];
    }
    rep(i, 0, k){
        cin >> b[i];
    }
    rep(i, 0, k){
        if(a[i] > b[i]) swap(a[i], b[i]);
        freq[a[i]][b[i]].push_back(i);
    }
    int c2 = 2 * sz(freq[2][2]);
    vi p, c;
    rep(i, 1, 4){
        int l = sz(freq[1][i]);
        for(int b = 1; l > 0; b *= 2){
            int v = min(l, b);
            p.push_back(i);
            c.push_back(v);
            l -= v;
        }
    }
    vector<vii> dp(sz(p) + 1, vii(c2 + 1, {0, -1}));
    dp[0][0] = {1, -1};
    rep(i, 0, sz(p)){
        int v = c[i] * p[i];
        rep(j, 0, sz(dp[i])){
            if(!dp[i][j].first) continue;
            if(j + v < sz(dp[i+1])){
                dp[i+1][j + v] = {1, 1};
            }
            dp[i+1][j] = {1, 0};
        }
    }
    // if(!dp[sz(p)][c2].first){
    //     cout << 0 << "\n";
    //     return 0;
    // }
    // assert(dp[sz(p)][c2].first);
    vi cnt(4);
    int cur = c2;
    for(int i = sz(p); i > 0; i--){
        if(dp[i][cur].second == 1){
            cnt[p[i-1]] += c[i-1];
            cur -= c[i-1] * p[i-1];
        }
    }
    vector<vi> grid(3, vi(n));
    int colstart = 0;
    for(int w : {2, 3}){
        for(int piece : freq[w][3]){
            rep(i, 0, 3){
                rep(j, 0, w){
                    grid[i][j + colstart] = piece + 1;
                }
            }
            colstart += w;
        }
    }
    int col2start = colstart;
    for(int piece : freq[2][2]){
        rep(i, 0, 2){
            rep(j, 0, 2){
                grid[i][j + col2start] = piece + 1;
            }
        }
        col2start += 2;
    }
    int col1start = colstart;
    rep(i, 1, 4){
        rep(_, 0, cnt[i]){
            assert(sz(freq[1][i]) >= 1);
            int piece = freq[1][i].back();
            freq[1][i].pop_back();
            rep(j, 0, i){
                grid[2][col1start] = piece + 1;
                col1start++;
            }
        }
    }
    assert(col1start == col2start);
    vi start = {col2start, col2start, col1start};
    while(sz(freq[1][3])){
        int piece = freq[1][3].back();
        freq[1][3].pop_back();
        rep(i, 0, 3){
            grid[i][start[i]] = piece + 1;
            start[i]++;
        }
        // colstart += 1;
    }
    for(int piece : freq[1][2]){
        if(start[2] < start[1]){
            grid[2][start[2]] = grid[2][start[2] + 1] = piece + 1;
            start[2] += 2;
        }
        else{
            grid[0][start[0]] = grid[1][start[1]] = piece + 1;
            start[0]++, start[1]++;
        }
    }
    for(int piece : freq[1][1]){
        bool use = false;
        rep(i, 0, 3){
            if(start[i] < n){
                grid[i][start[i]] = piece + 1;
                start[i]++;
                use = true;
                break;
            }
        }
        assert(use);
    }
    rep(i, 0, 3){
        rep(j, 0, n){
            assert(grid[i][j] != 0);
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}