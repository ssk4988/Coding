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

bool eq(char a, char b) {
    return tolower(a) == tolower(b);
}

int score(vector<string> board) {
    int ans = 0;
    while(true) {
        bool did = false;
        vvi rem(8, vi(8));
        rep(r, 0, 8) {
            vi run;
            auto apply = [&]() -> void {
                if(sz(run) < 3) {
                    run.clear();
                    return;
                }
                bool cascade = true;
                for(int c : run) {
                    rem[r][c] = did = true;
                    if(board[r][c] != board[r][run[0]]) cascade = false;
                }
                if(cascade) ans += 1000;
                ans += 100;
                if(sz(run) == 4) ans += 100;
                if(sz(run) >= 5) ans += 300;
                run.clear();
            };
            rep(c, 0, 8) {
                if(board[r][c] == ' ') {apply(); continue; }
                else if(sz(run) && !eq(board[r][c-1], board[r][c])) apply();
                run.pb(c);
            }
            apply();
        }
        rep(c, 0, 8) {
            vi run;
            auto apply = [&]() -> void {
                if(sz(run) < 3) {
                    run.clear();
                    return;
                }
                bool cascade = true;
                for(int r : run) {
                    rem[r][c] = did = true;
                    if(board[r][c] != board[run[0]][c]) cascade = false;
                }
                if(cascade) ans += 1000;
                ans += 100;
                if(sz(run) == 4) ans += 100;
                if(sz(run) >= 5) ans += 300;
                run.clear();
            };
            rep(r, 0, 8) {
                if(board[r][c] == ' ') {apply(); continue; }
                else if(sz(run) && !eq(board[r-1][c], board[r][c])) apply();
                run.pb(r);
            }
            apply();
        }
        vector<string> board2(8, string(8, ' '));
        rep(c, 0, 8) {
            int cur = 0;
            rep(r, 0, 8) {
                if(board[r][c] != ' ' && !rem[r][c]) {
                    board2[cur++][c] = board[r][c];
                }
            }
        }
        if(!did) break;
        board = board2;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        // row 0 is bottom
        vector<string> board(8);
        rep(i, 0, 8) {
            cin >> board[i];
        }
        reverse(all(board));
        int ans = 0;
        vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
        rep(sr, 0, 8) {
            rep(sc, 0, 8) {
                rep(k, 0, 4) {
                    int sr1 = sr + dr[k], sc1 = sc + dc[k];
                    if(min(sr1, sc1) < 0 || max(sr1, sc1) >= 8) continue;
                    swap(board[sr][sc], board[sr1][sc1]);
                    board[sr][sc] = tolower(board[sr][sc]);
                    board[sr1][sc1] = tolower(board[sr1][sc1]);
                    ans = max(ans, score(board));
                    swap(board[sr][sc], board[sr1][sc1]);
                    board[sr][sc] = toupper(board[sr][sc]);
                    board[sr1][sc1] = toupper(board[sr1][sc1]);   
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
