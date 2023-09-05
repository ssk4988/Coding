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
using vvl = vector<vl>;

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

// #pragma GCC optimize("Ofast, unroll-loops")

vector<array<int, 2>> ds = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

ll MOD = 1e9 + 9;
// ll mod(ll k)
// {
//     return k % MOD;
// }

using vvl = vector<vl>;

vvl matmul(vvl &a, vvl &b)
{
    vvl res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res))
    {
        rep(j, 0, sz(res[i]))
        {
            rep(k, 0, sz(a[0]))
            {
                res[i][j] = (res[i][j] + ((a[i][k] * b[k][j]) % MOD)) % MOD;
            }
        }
    }
    return res;
}

vvl matpow(vvl &b, ll p)
{
    // cout << "pow: " << p << nL;
    if (p == 1)
        return b;
    vvl res = matpow(b, p / 2);
    res = matmul(res, res);
    if (p % 2 == 1)
        res = matmul(res, b);
    // cout << "pow: " << p << nL;
    return res;
}
int n, m;

bool validspot(int b, int r, int c)
{
    for (auto [di, dj] : ds)
    {
        int i1 = r + di, j1 = c + dj;
        if (i1 < 0 || i1 >= 2 || j1 < 0 || j1 >= n)
            continue;
        if ((b >> (n * i1 + j1)) & 1)
            return false;
    }
    return true;
}
bool isvalid(int b)
{
    rep(i, 0, 2)
    {
        rep(j, 0, n)
        {
            if (((b >> (n * i + j)) & 1) == 0)
                continue;
            if (!validspot(b, i, j))
                return false;
        }
    }
    return true;
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    map<int, int> rl, rrl;
    if (m == 1)
    {
        cout << (1 << n) << nL;
        return 0;
    }
    auto extract = [&](int b) -> vvi
    {
        vvi board(2, vi(n));
        rep(i, 0, 2)
        {
            rep(j, 0, n)
            {
                board[i][j] = b & 1;
                b >>= 1;
            }
        }
        return board;
    };

    // case out m = 1, 2
    int bs = 1 << (n * 2);
    vvl start;
    rep(i, 0, bs)
    {
        // vvi bb = extract(i);
        if (isvalid(i))
        {
            rl[i] = sz(rl);
            rrl[rl[i]] = i;
            start.pb({1});
            // rep(a, 0, 2)
            // {
            //     rep(b, 0, n)
            //     {
            //         cout << (bb[a][b] ? "x" : ".");
            //     }
            //     cout << nL;
            // }
            // cout << nL;
        }
    }
    bs = sz(start);
    vvl mat(bs, vl(bs));
    rep(i, 0, bs)
    {
        rep(j, 0, bs)
        {
            // j transitions to i
            // first check if 2nd row of j matches 1st row of i
            int a = rrl[i], b = rrl[j];
            int j1 = (b >> n);
            int i1 = (a & ((1 << n) - 1));
            if (i1 != j1)
                continue;
            bool works = true;
            // vvi jb = extract(j);
            rep(k, 0, n)
            {
                if ((a & (1 << (n + k))) && !validspot(b, 2, k))
                    works = false;
            }
            if (works)
            {
                mat[i][j] = 1;
                // rep(a, 0, 2)
                // {
                //     rep(b, 0, n)
                //     {
                //         cout << (jb[a][b] ? "x" : ".");
                //     }
                //     cout << nL;
                // }
                // vvi ib = extract(i);
                // rep(a, 0, 2){
                //     rep(b, 0, n)
                //     {
                //         cout << (ib[a][b] ? "x" : ".");
                //     }
                //     cout << nL;
                // }
                // cout << nL;
            }
        }
    }
    vvl res;
    if (m == 2)
    {
        res = start;
    }
    else
    {
        res = matpow(mat, m - 2);
        res = matmul(res, start);
    }
    ll ans = 0;
    rep(i, 0, sz(res))
    {
        rep(j, 0, sz(res[i]))
        {
            ans = (ans + res[i][j]) % MOD;
        }
    }
    cout << ans << nL;
    // cout << bs << nL;

    return 0;
}
