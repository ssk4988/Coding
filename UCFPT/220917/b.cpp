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

#define maxN 20

int board[maxN][maxN];
ll ans = 0;
int n, m;
int nex[3][3];
unordered_map<string, string> transition;


bool check(int r, int c)
{
    bool valid = false;
    if (board[r - 1][c - 1] == -1 || board[r][c - 1] == -1 || board[r][c] == -1)
        valid = true;
    if (board[r][c] == board[r - 1][c - 1] && board[r][c] == board[r][c - 1])
        valid = true;
    if (board[r][c] != board[r - 1][c - 1] && board[r][c] != board[r][c - 1] && board[r][c - 1] != board[r - 1][c - 1])
        valid = true;
    // if(board[r][c] != -1){
    //     for(int i1 = c - 6; i1 >= 1; i1 -= 6){\
    //         if(board[r][i1] != board[r][c]){
    //             valid = false;
    //         }
    //     }
    // }
    
    return valid;
}

ll bts(int r, int c)
{
    // if (!check(r, c))
    //     return 0;
    ll cur = 0;
    bool isSet = board[r][c] != -1;
    int reps = isSet || c > 1 ? 1 : 3;
    rep(i, 0, reps)
    {
        board[r][c] = isSet ? board[r][c] : (c > 1 ? nex[board[r-1][c-1]][board[r][c-1]] : i);
        if (check(r, c))
        {
            if (c + 1 <= r)
            {
                cur += bts(r, c + 1);
            }
            else if (r + 1 <= n)
            {
                cur += bts(r + 1, 1);
            }
            else
            {
                cur += 1;
            }
        }
    }
    board[r][c] = isSet ? board[r][c] : -1;

    return cur;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n >> m;
    memset(board, -1, sizeof board);
    rep(i, 0, 3){
        rep(j, 0, 3){
            if(i == j) nex[i][j] = i;
            else nex[i][j] = 3 - i - j;
        }
    }
    rep(i, 0, m)
    {
        int r, c, v;
        cin >> r >> c >> v;
        board[r][c] = v;
    }
    if (m < 3)
    {
        ans = 1;
        rep(i, 0, n - m)
        {
            ans *= 3;
        }
    }
    else
    {
        ans = bts(1, 1);
    }
    cout << ans << nL;
    return 0;
}