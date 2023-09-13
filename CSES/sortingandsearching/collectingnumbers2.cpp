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
    vi arr(n), rev(n);
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
    auto cont = [&](int v)->int{
        int ans = 0;
        if(v && v < n) ans += rev[v] < rev[v - 1];
        // if(v + 1 < n) ans += rev[v + 1] < rev[v];
        return ans;
    };
    rep(i, 0, m)
    {
        int a, b; cin >> a >> b;
        a--, b--;
        set<int> rel;
        rel.insert(arr[a]);
        rel.insert(arr[a] + 1);
        rel.insert(arr[b]);
        rel.insert(arr[b] + 1);
        for(int i : rel) cnt -= cont(i);
        swap(rev[arr[a]], rev[arr[b]]);
        swap(arr[a], arr[b]);
        for(int i : rel) cnt += cont(i);
        cout << cnt << "\n";
    }

    return 0;
}
