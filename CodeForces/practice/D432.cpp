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
    string s;
    cin >> s;
    int n = (int)s.length();
    vector<int> pi(n + 1);
    vi freq(n + 1);
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
    vector<bool> ready(n + 1, false);
    int cnt = 1;
    ready[n] = true;
    int k = pi[n - 1];
    while (k > 0)
    {

        ready[k] = true;
        cnt++;
        k = pi[k - 1];
    }
    for (int i = n - 1; i > 0; i--)
    {
        freq[pi[i - 1]] += freq[i];
    }
    cout << cnt << nL;
    rep(i, 0, n + 1)
    {
        if (ready[i])
        {
            cout << i << " " << freq[i] + 1 << nL;
        }
    }

    return 0;
}