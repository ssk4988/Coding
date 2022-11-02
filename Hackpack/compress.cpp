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

    vi a;

    

    // FASTER
    int n = a.size();
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; ++i)
    {
        pairs[i] = {a[i], i};
    }
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i > 0 && pairs[i - 1].first != pairs[i].first)
            nxt++;
        a[pairs[i].second] = nxt;
    }

    // ALTERNATE (SHORT)
    vector<int> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    for (int i = 0; i < n; ++i)
    {
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
    }

    return 0;
}