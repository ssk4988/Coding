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
    string str;
    cin >> str;
    int n = (int)str.length();
    vector<int> z(n);
    vector<bool> end(n + 1, false);
    vi freq(n + 1, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        if (i + z[i] < n)
            freq[z[i]]++;
        while (i + z[i] < n && str[z[i]] == str[i + z[i]])
        {
            z[i]++;
            if (i + z[i] < n)
            {
                freq[z[i]]++;
            }
        }
        if (i + z[i] == n)
        {
            end[z[i]] = true;
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }

    int ans = -1;
    for (int i = n; i >= 1; i--)
    {
        freq[i - 1] += freq[i];
        if (freq[i] > 0 && end[i])
        {
            ans = i;
            break;
        }
    }
    if (ans == -1)
    {
        cout << "Just a legend" << nL;
    }
    else
    {
        cout << str.substr(0, ans);
    }

    return 0;
}