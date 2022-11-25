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

vector<int> suffixarray(string input)
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
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1 << k) < n)
    {
        vector<pair<pair<int, int>, int>> a(n);
        for(int i = 0; i < n; i++){
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        k++;
    }
    return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;

    vi sa = suffixarray(str);

    rep(i, 0, str.length() + 1)
    {
        cout << sa[i] << " ";
    }
    cout << nL;

    return 0;
}