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

ll pref[2][500][500][2];
ll ms[] = {1000000009, 1000000007};
const ll BASE = 7;
ll bpow[2][500];
ll mod(ll k, ll m)
{
    return (k % m + m) % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    unordered_map<char, int> map;
    map['A'] = 1;
    map['C'] = 2;
    map['G'] = 3;
    map['T'] = 4;
    int n, m;
    cin >> n >> m;
    string str;
    rep(i, 0, 2)
    {
        bpow[i][0] = 1;
        rep(j, 1, 500)
        {
            bpow[i][j] = mod(bpow[i][j - 1] * BASE, ms[i]);
        }
    }
    rep(i, 0, 2)
    {
        rep(j, 0, n)
        {
            cin >> str;
            rep(k, 0, m)
            {
                rep(l, 0, 2)
                {
                    pref[i][j][k][l] = mod(bpow[l][k] * map[str[k]], ms[l]);
                    if (k)
                    {
                        pref[i][j][k][l] = mod(pref[i][j][k][l] + pref[i][j][k - 1][l], ms[l]);
                    }
                }
            }
        }
    }
    int minans = m;
    int lo = 1;
    int hi = m;
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        bool w = false;
        rep(l, 0, m - mid + 1)
        {
            set<vector<ll>> spotty;
            bool works = true;
            rep(k, 0, 2)
            {
                rep(i, 0, n)
                {
                    vector<ll> cur(2, 0);
                    rep(j, 0, 2)
                    {
                        cur[j] = pref[k][i][l + mid - 1][j];
                        if (l)
                            cur[j] = mod(cur[j] - pref[k][i][l - 1][j], ms[j]);
                    }
                    if (k)
                    {
                        if (spotty.count(cur))
                        {
                            works = false;
                            break;
                        }
                    }
                    else
                    {
                        spotty.emplace(cur);
                    }
                }
            }
            if (works)
            {
                w = true;
                // cout << l << " " << mid << nL;
                break;
            }
        }
        if(w){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    cout << lo << nL;

    return 0;
}