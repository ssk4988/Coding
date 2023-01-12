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

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vvi c(n, vi(2, -1));
    rep(i, 0, n)
    {
        cin >> c[i][0] >> c[i][1];
    }
    // CHECK VERTICAL/HORIZONTAL LINES, n = 3
    sort(all(c));
    vector<vvi> m = vector<vvi>(3, vvi(2, vi(2, -1)));
    m[0][0][0] = 0;
    m[0][0][1] = 1;
    m[1][0][0] = 0;
    m[1][0][1] = 2;
    m[2][0][0] = 1;
    m[2][0][1] = 2;
    vvi ans(2, vi(3, -1));
    vector<unordered_set<int>> cs(2);
    bool rev = false;
    rep(i, 0, n)
    {
        rep(j, 0, 2)
        {
            cs[j].insert(c[i][j]);
        }
    }
    if(cs[0].size() == 1){
        swap(cs[0], cs[1]);
        rep(i, 0, n){
            swap(c[i][0], c[i][1]);
        }
        sort(all(c));
        rev = true;
    }
    rep(i, 0, 3)
    {
        ans[0][0] = c[m[i][0][0]][0];
        ans[0][2] = c[m[i][0][1]][0] - ans[0][0];
        for (int l = ans[0][0]; cs[0].find(l) != cs[0].end(); l += ans[0][2])
        {
            ans[0][1] = l;
        }
        vi other;
        rep(j, 0, n)
        {
            if (ans[0][0] <= c[j][0] && c[j][0] <= ans[0][1] && (c[j][0] - ans[0][0]) % ans[0][2] == 0)
            {
            }
            else
            {
                other.pb(c[j][1]);
            }
        }
        if (other.size() == 0)
        {
            other.pb(c[0][1]);
        }
        sort(all(other));
        ans[1][0] = other[0];
        ans[1][1] = other.back();
        ans[1][2] = other.back() - other[0];
        rep(j, 0, other.size() - 1)
        {
            ans[1][2] = gcd(ans[1][2], other[j + 1] - other[j]);
        }
        bool works = true;
        rep(j, 0, n)
        {
            bool w1 = false;
            rep(k, 0, 2)
            {
                if (ans[k][0] <= c[j][k] && c[j][k] <= ans[k][1] && (ans[k][2] == 0 || (c[j][k] - ans[k][0]) % ans[k][2] == 0))
                {
                    w1 = true;
                }
            }
            if (!w1)
            {
                works = false;
            }
        }
        for (int l = ans[1][0]; ans[1][2] != 0 && l <= ans[1][1]; l += ans[1][2])
        {
            if (cs[1].find(l) == cs[1].end())
            {
                works = false;
            }
        }
        if (works)
            break;
        else
        {
            ans = vvi(2, vi(3, -1));
        }
    }
    if(rev){
        rep(i, 0, 3){
            swap(ans[0][i], ans[1][i]);
        }
    }
    rep(i, 0, 2)
    {
        rep(j, 0, 3)
        {
            cout << ans[i][j];
            if (i == 1 && j == 2)
                cout << nL;
            else
                cout << " ";
        }
    }

    return 0;
}