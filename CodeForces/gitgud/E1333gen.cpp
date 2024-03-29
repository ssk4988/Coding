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

pair<bool, int> solve(vvi grid, bool queen)
{
    int n = sz(grid);
    int curr, curc;
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            if (grid[i][j] == 0)
                curr = i, curc = j;
        }
    }
    int cost = 0;
    grid[curr][curc] = -1;
    int inrow = true;
    rep(_, 0, n * n - 1)
    {
        tuple<int, int, int> mn = {1e9, -1, -1};
        rep(i, 0, n)
        {
            rep(j, 0, n)
            {
                if (grid[i][j] != -1 && ((i == curr || j == curc) || (queen && (i + j == curr + curc || i - j == curr - curc))))
                    mn = min(mn, {grid[i][j], i, j});
            }
        }
        int w;
        // tie(w, curr, curc) = mn;
        // if(w == 1e9){
        if (get<0>(mn) == 1e9)
        {
            rep(i, 0, n)
            {
                rep(j, 0, n)
                {
                    if (grid[i][j] != -1)
                        mn = min(mn, {grid[i][j], i, j});
                }
            }
            cost++;
        }
        if(w != _+1) inrow = false;
        tie(w, curr, curc) = mn;
        grid[curr][curc] = -1;
    }
    return {inrow, cost};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n = 3;
    vi perm;
    vi used(n * n);
    map<pi, vector<vvi>> cnt;
    auto gen = [&](auto &&gen) -> void
    {
        if (sz(perm) == n * n)
        {
            vvi grid(n, vi(n));
            rep(i, 0, n)
            {
                rep(j, 0, n)
                {
                    grid[i][j] = perm[i * n + j];
                }
            }
            if (grid[0][0] != 0 && grid[0][1] != 0 && grid[1][1] != 0)
                return;
            auto [rookrow, rook] = solve(grid, false);
            auto [queenrow, queen]= solve(grid, true);
            if (rook < queen)
            {
                cnt[{rook, queen}].pb(grid);
                // if (grid[0][0] != n * n - 1 && grid[0][2] != n * n - 1 && grid[2][0] != n * n - 1 && grid[2][2] != n * n - 1)
                // {
                //     cout << "bruh\n";
                // }
                if(grid[0][0] == 0){
                    rep(i, 0, n)
                    {
                        rep(j, 0, n) cout << grid[i][j] << " ";
                        cout << "\n";
                    }
                    cout << rook << " " << queen << "\n";
                }
            }
            return;
        }
        rep(i, 0, sz(used))
        {
            if (used[i])
                continue;
            perm.pb(i);
            used[i] = true;
            gen(gen);
            perm.pop_back();
            used[i] = false;
        }
    };
    gen(gen);
    for (auto [key, val] : cnt)
    {
        cout << key.f << " " << key.s << " " << sz(val) << "\n";
    }

    return 0;
}
