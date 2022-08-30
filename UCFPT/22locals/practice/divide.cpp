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
ll freq[10000001];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(freq, 0, sizeof freq);
    int n;
    cin >> n;
    int a[n];
    ll ans = 0;
    int last = 0;
    rep(i, 0, n)
    {
        cin >> a[i];
        freq[a[i]]++;
        last = max(last, a[i]);
    }
    rep(i, 1, 10000001)
    {
        if (freq[i])
        {
            for (int j = 2 * i; j <= last; j += i)
            {
                if (freq[j])
                {
                    ans += freq[i] * freq[j];
                }
            }
        }
    }
    ans += freq[0] * (n - freq[0]);
    cout << ans << nL;
    return 0;
}