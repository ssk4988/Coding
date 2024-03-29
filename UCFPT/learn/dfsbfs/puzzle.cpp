#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vvi target = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    map<vvi, int> seen;
    seen[target] = 0;
    queue<vvi> q;
    q.push(target);
    vi dr = {1, 0, -1, 0}, dc = {0, 1, 0, -1};
    while(!q.empty()){
        vvi board = q.front(); q.pop();
        int move = seen[board];
        int r, c;
        rep(i, 0, 3){
            rep(j, 0, 3){
                if(board[i][j] == 0){
                    r = i, c = j;
                    break;
                }
            }
        }
        rep(i, 0, 4){
            int r1 = r + dr[i], c1 = c + dc[i];
            if(r1 < 0 || c1 < 0 || r1 >= 3 || c1 >= 3) continue;
            swap(board[r][c], board[r1][c1]);
            if(!seen.count(board)){
                seen[board] = move + 1;
                q.push(board);
            }
            swap(board[r][c], board[r1][c1]);
        }
    }
    rep(cn, 0, nc){
        vvi board(3, vi(3));
        rep(i, 0, 3){
            rep(j, 0, 3){
                cin >> board[i][j];
            }
        }
        cout << seen[board] << "\n";
    }
    
    return 0;
}
