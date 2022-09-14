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

int cnt(bool a[4])
{
    int cnt = 0;
    rep(i, 0, 4)
    {
        if (a[i])
            cnt++;
    }
    return cnt;
}
void clear(bool a[4])
{
    rep(i, 0, 4)
    {
        a[i] = false;
    }
}

int main()
{
    freopen("second_second_friend_input.txt", "r", stdin);
    freopen("b2output.txt", "w", stdout);
    int nc;
    cin >> nc;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    rep(cn, 0, nc)
    {
        int r, c;
        cin >> r >> c;
        bool empty[r][c];
        bool tree[r][c];
        bool neighbors[r][c][4];
        string s;
        rep(i, 0, r)
        {
            cin >> s;
            rep(j, 0, c)
            {
                if (s[j] == '.')
                {
                    empty[i][j] = true;
                    tree[i][j] = false;
                }
                else
                {
                    empty[i][j] = false;
                    tree[i][j] = s[j] == '^';
                }
            }
        }
        deque<pi> q;
        rep(i, 0, r)
        {
            rep(j, 0, c)
            {
                if (!(empty[i][j] || tree[i][j]))
                    continue;
                rep(k, 0, 4)
                {
                    int r1 = i + dx[k];
                    int c1 = j + dy[k];
                    if (r1 >= 0 && r1 < r && c1 >= 0 && c1 < c && (empty[r1][c1] || tree[r1][c1]))
                    {
                        neighbors[i][j][k] = true;
                    }
                }
                if (cnt(neighbors[i][j]) == 1)
                {
                    clear(neighbors[i][j]);
                    q.push_back(mp(i, j));
                }
            }
        }
        while (q.size())
        {
            pi p = q.front();
            q.pop_front();
            if (cnt(neighbors[p.f][p.s]) != 0)
            {
                continue;
            }
            clear(neighbors[p.f][p.s]);
            rep(k, 0, 4)
            {
                int r1 = p.f + dx[k];
                int c1 = p.s + dy[k];
                if (r1 >= 0 && r1 < r && c1 >= 0 && c1 < c && cnt(neighbors[r1][c1]) > 0)
                {
                    neighbors[r1][c1][(k + 2) % 4] = false;
                    if (cnt(neighbors[r1][c1]) < 2)
                    {
                        clear(neighbors[r1][c1]);
                        q.push_back(mp(r1, c1));
                    }
                }
            }
        }
        bool works = true;
        for (int i = 0; i < r && works; i++)
        {
            for (int j = 0; j < c && works; j++)
            {
                if (empty[i][j] && cnt(neighbors[i][j]) >= 2)
                {
                    tree[i][j] = true;
                    empty[i][j] = false;
                }
                if (tree[i][j] && cnt(neighbors[i][j]) < 2)
                {
                    works = false;
                    break;
                }
            }
        }
        printf("Case #%d: %s\n", (cn + 1), works ? "Possible" : "Impossible");
        if (works)
        {
            rep(i, 0, r)
            {
                char o[c + 1];
                rep(j, 0, c)
                {
                    if (tree[i][j])
                        o[j] = '^';
                    else if (empty[i][j])
                        o[j] = '.';
                    else
                        o[j] = '#';
                }
                o[c] = 0;
                cout << o << nL;
            }
        }
    }

    return 0;
}