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

struct FT
{
    vector<ll> s;
    int n;
    FT(int n) : s(n), n(n) {}
    void update(int pos, ll dif)
    { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    ll query(int pos)
    { // sum of values in [0, pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
    int lower_bound(ll sum)
    { // min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
        {
            if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi a(n);
    int mx = 0;
    set<int> ss;
    unordered_map<int, int> rl;
    rep(i, 0, n)
    {
        cin >> a[i];
        ss.insert(a[i]);
    }
    for (int i : ss)
        rl[i] = sz(rl);
    rep(i, 0, n)
    {
        a[i] = rl[a[i]];
        mx = max(mx, a[i]);
    }
    vl invleft(n), invright(n + 1);
    FT ft(n + 5);
    rep(i, 0, n)
    {
        invleft[i] = ft.query(n) - ft.query(a[i] + 1);
        ft.update(a[i], 1);
    }
    ft = FT(n + 5);
    for (int i = n - 1; i >= 0; i--)
    {
        invright[i] = ft.query(ft.n) - ft.query(a[i] + 1);
        ft.update(a[i], 1);
    }
    ll ans = 0;
    rep(i, 0, n)
    {
        ans += min(invleft[i], invright[i]);
    }
    cout << ans << nL;

    return 0;
}
