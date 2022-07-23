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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    int arr[n], rev[n];
    int cnt = 1;
    rep(i, 0, n)
    {
        cin >> arr[i];
        arr[i]--;
        rev[arr[i]] = i;
    }
    rep(i, 0, n - 1)
    {
        if (rev[i + 1] < rev[i])
            cnt++;
    }
    rep(i, 0, m)
    {
        set<int> check;
        int a[2];
        rep(j, 0, 2)
        {
            cin >> a[j];
            a[j]--;
            if (arr[a[j]] - 1 >= 0)
                check.insert(arr[a[j]] - 1);
            if (arr[a[j]] + 1 < n)
                check.insert(arr[a[j]]);
        }
        for (int c : check)
        {
            if (rev[c] > rev[c + 1])
                cnt--;
        }
        rev[arr[a[0]]] = a[1];
        rev[arr[a[1]]] = a[0];
        int tmp = arr[a[0]];
        arr[a[0]] = arr[a[1]];
        arr[a[1]] = tmp;
        for (int c : check)
        {
            if (rev[c] > rev[c + 1])
                cnt++;
        }
        cout << cnt << "\n";
    }

    return 0;
}