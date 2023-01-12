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

void update(vector<ll> &bit, int idx, ll val)
{
    idx++;
    while (idx < bit.size())
    {
        bit[idx] += val;
        idx += idx & -idx;
    }
}

ll sum(vector<ll> &bit, int idx)
{
    idx++;
    ll ans = 0;
    while (idx > 0)
    {
        ans += bit[idx];
        idx -= idx & -idx;
    }
    return ans;
}

void range_update(vector<ll> &bit1, vector<ll> &bit2, int l, int r, ll x)
{
    update(bit1, l, x);
    update(bit1, r + 1, -x);
    update(bit2, l, x * (l - 1));
    update(bit2, r + 1, -x * r);
}

ll range_sum(vector<ll> &bit1, vector<ll> &bit2, int idx)
{
    ll ans = sum(bit1, idx) * idx - sum(bit2, idx);
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int n = 100;
    // vl b1(n + 1), b2(n + 1);
    // range_update(b1, b2, 0, 4, 1);
    // range_update(b1, b2, 2, 10, 2);
    // range_update(b1, b2, 7, 13, 3);
    // cout << range_sum(b1, b2, 5) - range_sum(b1, b2, 1) << nL;  // 2,5
    // cout << range_sum(b1, b2, 3) - range_sum(b1, b2, -1) << nL; // 0,3
    // cout << range_sum(b1, b2, 3) - range_sum(b1, b2, 0) << nL;  // 2,5
    // cout << range_sum(b1, b2, 9) - range_sum(b1, b2, 2) << nL;  // 3,9
    string str;
    cin >> str;
    int n = str.length();
    int nq;
    cin >> nq;
    vl bit[1 << 6][2];
    rep(i, 0, 1 << 6)
    {
        rep(j, 0, 2)
        {
            bit[i][j] = vl(n + 2);
        }
    }
    int start = 0;
    range_update(bit[start][0], bit[start][1], 0, 0, 1);
    rep(i, 0, n)
    {
        start ^= 1 << (str[i] - 'a');
        range_update(bit[start][0], bit[start][1], i + 1, i + 1, 1);
    }
    rep(i, 0, nq)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            ll ans = 0;
            rep(j, 0, 1 << 6)
            {
                ll q = range_sum(bit[j][0], bit[j][1], r) - range_sum(bit[j][0], bit[j][1], l - 1);
                ans += q * (q - 1) / 2;
            }
            cout << ans << nL;
        }
        else
        {
            int idx;
            char c;
            cin >> idx >> c;
            int v = c - 'a';
        }
    }

    return 0;
}