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

#define maxN 100005

ll m = 1000000003;

vector<ll> pows;

ll mod(ll k)
{
    return (k % m + m) % m;
}

ll strhash(string str)
{
    ll h = 0;
    for (char c : str)
    {
        h = mod(mod(h * 2020) + c);
    }
    return h;
}
ll strhash1(string str)
{
    ll h = 0;
    rep(i, 0, str.length()){
        h = mod(h + mod(pows[str.length() - 1 - i] * str[i]));
    }
    return h;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    pows.pb(nc);
    vector<ll> p1;
    rep(cn, 0, nc)
    {
        
        string a, b;
        cin >> a >> b;
        cin >> m;
        pows.clear();
        pows.pb(1);
        rep(i, 1, maxN)
        {
            pows.pb(mod(pows.back() * 2020));
        }
        string c = a + b;
        string ans1, ans2;
        reverse(all(c));
        vector<pair<ll, int>> arr;
        vector<pair<ll, pair<int, int>>> diff;
        rep(i, 0, pows.size())
        {
            arr.pb({pows[i], i});
        }
        sort(all(arr));
        vi freq(100, 0);
        rep(i, 0, arr.size() - 1)
        {
            diff.pb(mp(abs(arr[i].f - arr[i + 1].f), mp(arr[i].s, arr[i + 1].s)));
            if (diff.back().f < 100)
            {
                freq[diff.back().f]++;
            }
        }

        sort(all(diff));
        int d;
        pair<int, int> ind;
        rep(i, 0, diff.size())
        {
            if (diff[i].s.f < c.length() + 2 || diff[i].s.s < c.length() + 2)
                continue;
            d = diff[i].f;
            ind = diff[i].s;
            break;
        }
        string a1 = (char)('a' + d) + c;
        string b1 = (char)('a') + c;
        
        while (a1.length() < ind.f)
        {
            a1 += 'a';
        }
        while (b1.length() < ind.s)
        {
            b1 += 'a';
        }
        a1 += 'b';
        b1 += 'b';
        int c1 = max(a1.length(), b1.length()) + 20;
        while (a1.length() < c1)
        {
            a1 += 'a';
        }
        while (b1.length() < c1)
        {
            b1 += 'a';
        }
        reverse(all(a1));
        reverse(all(b1));
        cout << a1 << nL << b1 << nL;
        // cout << strhash(a1) << nL << strhash(b1) << nL;
    }
    return 0;
}