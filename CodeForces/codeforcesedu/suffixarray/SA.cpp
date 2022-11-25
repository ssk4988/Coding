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

void count_sort(vector<int> &p, vector<int> &c)
{
    int n = p.size();

    vector<int> cnt(n);
    for (auto x : c)
    {
        cnt[x]++;
    }
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++)
    {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto x : p)
    {
        p_new[pos[c[x]]++] = x;
    }
    p = p_new;
}

vector<int> suffixarray(string &input)
{
    string str = input + "$";
    int n = str.length();
    vector<int> p(n), c(n);
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {str[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++)
            p[i] = a[i].second;
        c[p[0]] = 0;

        for (int i = 1; i < n; i++)
        {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }
    }

    int k = 0;
    while ((1 << k) < n)
    {
        for (int i = 0; i < n; i++)
        {
            p[i] = (p[i] - (1 << k) + n) % n;
        }
        count_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (cur != prev);
        }
        c = c_new;
        k++;
    }
    return p;
}

vector<int> getlcp(string &input, vector<int> &sa)
{
    string str = input + "$";
    int n = str.length();
    vector<int> lcp(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++)
    {
        c[sa[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int pi = c[i];
        int j = sa[pi - 1];
        while (str[i + k] == str[j + k])
            k++;
        lcp[c[i]] = k--;
        k = max(k, 0);
    }
    return lcp;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;

    return 0;
}