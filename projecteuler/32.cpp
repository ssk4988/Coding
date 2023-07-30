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
    unordered_set<int> ans;
    rep(i, 1, 1'000'000)
    {
        string is = to_string(i);
        vi iused(10);
        for (char j : is)
            iused[j - '0'] = true;
        if (iused[0])
            continue;
        rep(j, 1, 1'000'000)
        {
            string js = to_string(j);
            ll prod = ll(i) * j;
            string ps = to_string(prod);
            if (sz(is) + sz(ps) + sz(js) > 9)
                break;
            if (sz(is) + sz(ps) + sz(js) != 9)
                continue;
            bool jcheck = true;
            vi jused(10);
            for (char k : js)
            {
                if (iused[k - '0'])
                {
                    jcheck = false;
                }
                jused[k - '0'] = true;
                if (k == '0')
                    jcheck = false;
            }
            for (char k : ps)
            {
                if (iused[k - '0'] || jused[k - '0'])
                    jcheck = false;
                if (k == '0')
                    jcheck = false;
                jused[k - '0'] = true;
            }
            rep(k, 1, 10){
                if(!(iused[k] || jused[k])) jcheck = false;
            }
            if (jcheck)
            {
                ans.insert(prod);
                cout << i << " " << j << " " << prod << nL;
            }
        }
    }
    ll sum = 0;
    for (int j : ans)
    {
        // cout << j << nL;
        sum += j;
    }
    cout << ans.count(7254) << nL;
    cout << sum << nL;
    return 0;
}