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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    set<ll> set;
    map<ll, int> start;
    map<ll, int> end;
    ll cnt[n + 5] = {0};
    rep(i, 0, n)
    {
        ll l, r;
        cin >> l >> r;
        start[l]++;
        end[r]++;
        set.insert(l);
        set.insert(r);
    }
    int cur = 0;
    for (auto it = set.begin(); it != set.end(); it++)
    {
        if (start.find(*it) != start.end())
        {
            cur += start[*it];
        }
        cnt[cur]++;
        if (end.find(*it) != end.end())
        {
            cur -= end[*it];
        }
        if (next(it) != set.end())
        {
            cnt[cur] += *next(it) - *it - 1;
        }
    }
    rep(i, 1, n + 1)
    {
        cout << cnt[i] << " ";
    }
    cout << nL;

    return 0;
}