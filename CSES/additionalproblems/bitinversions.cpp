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

set<int> s;
map<int, int> m;
int n;

void change(int k, int v)
{
    m[k] += v;
    if (!m[k])
        m.erase(k);
}

void fix(int k)
{
    if (k == 0 || k == n)
        return;
    auto it = s.find(k);
    if (it == s.end())
    {
        s.insert(k);
        it = s.find(k);
        change(*next(it) - *prev(it), -1);
        change(*next(it) - *it, 1);
        change(*it - *prev(it), 1);
    }
    else
    {
        change(*next(it) - *prev(it), 1);
        change(*next(it) - *it, -1);
        change(*it - *prev(it), -1);
        s.erase(k);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s1;
    cin >> s1;

    char c = ' ';
    n = s1.length();
    rep(i, 0, n)
    {
        if (s1[i] != c)
        {
            s.insert(i);
        }
        c = s1[i];
    }
    s.insert(n);

    int p = -1;
    for (int v : s)
    {
        m[v - p]++;
        p = v;
    }
    int q;
    cin >> q;
    rep(i, 0, q)
    {
        int k;
        cin >> k;
        k--;
        fix(k);
        fix(k + 1);
        cout << m.rbegin()->first << " ";
    }
    cout << nL;

    return 0;
}