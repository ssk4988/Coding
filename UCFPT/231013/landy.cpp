#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp> //gp_hash_table

#define all(a) a.begin(), a.end()
#define pb push_back
#define eb emplace_back
#define sz(a) (int)a.size()
#define bitcount(a) (int)__builtin_popcount(a)
#define bitcountll(a) (int)__builtin_popcountll(a)
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define fora(x, o) for (auto &x : o)
#define bitat(x, i) (((x) >> (i)) & 1)

using namespace std;
// using namespace __gnu_pbds;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<ll> vll;

template <class T, class U>
istream &operator>>(istream &is, pair<T, U> &p)
{
    is >> p.first >> p.second;
    return is;
}
template <class T>
istream &operator>>(istream &is, vector<T> &vec)
{
    for (auto &x : vec)
        cin >> x;
    return is;
}
template <class T, class U>
ostream &operator<<(ostream &os, pair<T, U> &p)
{
    os << "<" << p.first << "," << p.second << ">";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, vector<T> &vec)
{
    for (auto x : vec)
        os << x << " ";
    return os;
}

int CaseN;

vi Z(const string &S)
{
    vi z(sz(S)), diff(sz(S), sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S))
    {
        z[i] = 0;
        if (i < r)
        {
            vi diff_cands;
            if (i <= diff[l] + l && diff[l] != sz(S))
                diff_cands.push_back(diff[l] + l);
            if (diff[i - l] + i < r)
                diff_cands.push_back(diff[i - l] + i);
            sort(all(diff_cands));
            diff_cands.erase(unique(all(diff_cands)), diff_cands.end());
            z[i] = min(r - i, z[i - l]);
            for (int j : diff_cands)
                if (S[j] != S[j - i])
                {
                    if (j - i < diff[i])
                        diff[i] = j - i;
                    else
                        z[i] = min(z[i], j - i);
                }
        }
        while (i + z[i] < sz(S))
        {
            if (S[i + z[i]] != S[z[i]])
            {
                if (diff[i] < z[i])
                    break;
                diff[i] = z[i];
            }
            z[i]++;
        }
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    cout << S << "\n";
    cout << z << endl;
    cout << diff << endl;
    return z;
}

const ll mod = 998244353;

void solve()
{
    string s, t;
    cin >> s >> t;

    string comb = t + s;
    vi z = Z(comb);
    // cout << z << "\n";

    vector<vll> dp(sz(s) + 2, vll(3));
    vector<vll> sum(sz(s) + 2, vll(3));
    dp[sz(s)] = sum[sz(s)] = {1, 0, 0};

    for (int i = sz(s) - 1; i >= 0; i--)
    {
        int match = min(sz(t), z[i + sz(t)]);
        // cout << match << endl;
        for (int j = 0; j < 3; j++)
            dp[i][j] = (sum[i + 1][j] + mod - sum[i + match + 1][j]) % mod;
        (dp[i][2] += 2 * dp[i][1] + dp[i][0]) %= mod;
        (dp[i][1] += dp[i][0]) %= mod;
        for (int j = 0; j < 3; j++)
            sum[i][j] = (sum[i + 1][j] + dp[i][j]) % mod;
    }
    cout << dp[0][2] << "\n";
}

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("input.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);
    cout << fixed;
    // int t; cin >> t; for(CaseN = 1; CaseN <= t; ++CaseN) solve(); /*
    CaseN = 1;
    solve(); /**/
    cout.flush();
    return 0;
}
