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
    int m[2000][26] = {0};

    int c[n];
    rep(i, 0, n)
    {
        c[i] = set[i] - 'a';
    }
    rep(i, 1, n + 1)
    {
        int l = 0;
        int r = 0;
        int cnt[26] = {0};
        while (r < n)
        {
            while (r < n && r - l < i)
            {
                cnt[c[r++]]++;
            }
            rep(j, 0, 26)
            {
                m[i][j] = max(m[i][j], cnt[j]);
            }
            cnt[c[l++]]--;
        }
    }
    int q;
    cin >> q;
    rep(i, 0, q)
    {
        int num;
        char c1;
        cin >> num >> c1;
        int v = c1 - 'a';
        int lo = 0;
        int hi = n;
        while (lo < hi)
        {
            int mid = lo + (hi - lo + 1) / 2;
            if (num + m[mid][v] >= mid)
            {
                lo = mid;
            }
            else
            {
                hi = mid - 1;
            }
        }
        cout << lo << nL;
    }

    return 0;
}