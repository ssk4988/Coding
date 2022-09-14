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

int freq[1000001];
int n;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    int arr[n];

    rep(i, 0, n)
    {
        cin >> arr[i];
        for (int j = 1; j * j <= arr[i]; j++)
        {
            if (arr[i] % j == 0)
            {
                freq[j]++;
                if (j * j != arr[i])
                    freq[arr[i] / j]++;
            }
        }
    }
    int ans = 0;
    rep(i, 0, 1000001)
    {
        if (freq[i] > 1)
        {

            ans = max(ans, i);
        }
    }
    cout << ans << nL;

    return 0;
}