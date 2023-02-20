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

ll m = 1e9 + 7;

bool DEBUG = false;

ll mod(ll k)
{
    return k % m;
}

vector<vector<vl>> combine(vector<vector<vl>> &left, vector<vector<vl>> &right)
{
    vector<vector<vl>> res(10, vector<vl>(10, vl(9)));
    rep(j, 0, 10)
    {
        rep(k, 0, 10)
        {
            rep(l, 0, 9)
            {
                if (left[j][k][l] == 0)
                    continue;
                rep(j1, 0, 10)
                {
                    if (k == j1)
                        continue;
                    rep(k1, 0, 10)
                    {
                        rep(l1, 0, 9)
                        {
                            if (right[j1][k1][l1] == 0)
                                continue;
                            res[j][k1][(l + l1) % 9] = mod(res[j][k1][(l + l1) % 9] + mod(left[j][k][l] * right[j1][k1][l1]));
                        }
                    }
                }
            }
        }
    }
    return res;
};

vector<vector<vector<vl>>> jump;

vector<vector<vl>> build(ll digs)
{
    vector<vector<vl>> res;
    int highestbit = 63 - __builtin_clzll(digs);
    digs -= (1LL << highestbit);
    res = jump[highestbit];
    for (; highestbit >= 0; highestbit--)
    {
        ll bit = 1LL << highestbit;
        if ((bit & digs) == 0)
            continue;
        res = combine(res, jump[highestbit]);
        digs -= bit;
    }
    return res;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // case out a <= 3
    ll a;
    int b;
    cin >> a >> b;
    auto start = chrono::high_resolution_clock::now();
    // a = 12345, b = 200;
    if (a <= 3)
    {
        // vector<vector<vl>> test(10, vector<vl>(10, vl(9)));
        set<int> anss;
        rep(i, 1, 10)
        {
            rep(j, 0, 10)
            {
                rep(k, 0, 10)
                {
                    if (i == j || j == k)
                        continue;
                    int v = i * 100 + j * 10 + k;
                    rep(l, 0, 3 - a)
                    {
                        v /= 10;
                    }
                    if (v % 225 != b)
                        continue;
                    anss.insert(v);
                }
            }
        }
        cout << anss.size() << nL;
        return 0;
    }
    int highestbit = 64 - __builtin_clzll(a);
    jump = vector<vector<vector<vl>>>(highestbit, vector<vector<vl>>(10, vector<vl>(10, vl(9))));
    // brute force first dig, last 2
    rep(i, 0, 10)
    {
        jump[0][i][i][i % 9]++;
    }

    rep(i, 1, sz(jump))
    {
        vector<vector<vl>> res = combine(jump[i - 1], jump[i - 1]);
        jump[i] = res;
    }

    // vector<vector<vl>> test(10, vector<vl>(10, vl(9)));
    // rep(i, 0, 10)
    // {
    //     rep(j, 0, 10)
    //     {
    //         // rep(k, 0, 10)
    //         // {
    //             rep(l, 0, 10)
    //             {
    //                 if (i == j || j == l)//k || k == l)
    //                     continue;
    //                 test[i][l][(i + j + 0 + l) % 9]++;
    //             }
    //         // }
    //     }
    // }
    a -= 3;
    vector<vector<vl>> calc = build(a);
    ll ans = 0;
    int b1 = b % 25;
    int b2 = b % 9;

    rep(j, 0, 10)
    { // 2nd to last digit
        rep(k, 0, 10)
        { // last digit
            if (j == k)
                continue;
            if ((10 * j + k) % 25 != b1)
                continue;
            rep(i, 1, 10)
            { // first digit
                rep(l, 0, 9)
                { // mod of inside - can make it equal to exact value needed for speedup
                    if ((l + i + j + k) % 9 != b2)
                        continue;
                    rep(d1, 0, 10)
                    { // left dig
                        if (i == d1)
                            continue;
                        rep(d2, 0, 10)
                        { // right dig
                            if (d2 == j)
                                continue;
                            ans = mod(ans + calc[d1][d2][l]);
                        }
                    }
                }
            }
        }
    }
    cout << ans << nL;
    if (DEBUG)
    {
        auto end = chrono::high_resolution_clock::now();
        double time_taken =
            chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        time_taken *= 1e-9;

        cout << "Time taken by program is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec" << nL;
    }

    // rep(i, 0, 10)
    // {
    //     rep(j, 0, 10)
    //     {
    //         rep(k, 0, 9)
    //         {
    //             if (test[i][j][k] != calc[i][j][k])
    //                 cout << i << " " << j << " " << k << " " << test[i][j][k] << " " << calc[i][j][k] << nL;
    //         }
    //     }
    // }

    return 0;
}
