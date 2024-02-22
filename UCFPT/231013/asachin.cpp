#include <bits/stdc++.h>

#define all(a) a.begin(), a.end()
#define pb push_back
#define sz(a) (int)a.size()
#define rep(i, from, to) for (int i = from; i < (to); ++i)

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vvi;
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
    vvi z(2, vi(sz(S)));
    int l = -1, r = -1;
    int times = 0;
    rep(i, 1, sz(S))
    {
        int diff = 0;
        if (i < r)
        {
            rep(j, 0, 2)
                z[j][i] = min(r - i, z[j][i - l]);
            vi diff_cands;
            if (i <= z[0][l] + l)
                diff_cands.push_back(z[0][l] + l);
            if (z[0][i - l] + i < r)
                diff_cands.push_back(z[0][i - l] + i);
            sort(all(diff_cands));
            diff_cands.erase(unique(all(diff_cands)), diff_cands.end());
            for (int j : diff_cands)
                if (S[j] != S[j - i])
                {
                    z[diff][i] = min(z[diff][i], j - i);
                    diff++;
                }
        }
        while (diff < 2 && i + z[diff][i] < sz(S))
        {
            if (S[i + z[diff][i]] != S[z[diff][i]])
            {
                diff++;
                if(diff >= 2) continue;
                z[diff][i] = z[diff - 1][i];
            }
            times++;
            z[diff][i]++;
        }
        z[1][i] = max(z[1][i], z[0][i]);
        if (i + z[1][i] > r)
            l = i, r = i + z[1][i];
    }
    assert(times <= 2 * sz(S));
    return z[1];
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
