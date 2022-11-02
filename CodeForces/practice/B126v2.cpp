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
    string s;
    cin >> s;
    int n = (int)s.length();
    vector<int> pi(n);
    vector<int> freq(n + 1);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
        freq[pi[i]]++;
    }
    int ans = -1;
    int k = pi[n - 1];
    freq[k]--;
    while (k > 0)
    {
        if (freq[k])
        {
            ans = k;
            break;
        }
        k = pi[k - 1];
    }
    if (ans == -1)
    {
        cout << "Just a legend" << nL;
    }
    else
    {
        cout << s.substr(0, ans) << nL;
    }

    return 0;
}