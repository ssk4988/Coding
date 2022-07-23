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
    string set;
    cin >> set;
    unordered_set<char> s1;
    rep(i, 0, n)
    {
        s1.insert(set[i]);
    }
    int k = s1.size();
    unordered_map<char, int> m;
    for (char c : s1)
    {
        m[c] = 0;
    }
    int l = 0;
    int r = -1;
    int best = n;
    unordered_set<char> s2;
    while (r < n && l < n)
    {
        while (s2.size() < k && r + 1 < n)
        {
            r++;
            m[set[r]]++;
            s2.insert(set[r]);
        }
        if (s2.size() < k)
            break;
        while (l <= r && m[set[l]] > 1)
        {
            m[set[l]]--;
            l++;
        }
        best = min(r - l + 1, best);
        if (l <= r)
        {
            m[set[l]]--;
            if (m[set[l]] == 0)
            {
                s2.erase(set[l]);
            }
            l++;
        }
    }
    cout << best << nL;
    return 0;
}