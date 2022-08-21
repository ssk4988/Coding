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

bool cmp(pair<int, pi> p1, pair<int, pi> p2)
{
    return p1.f < p2.f;
}
void update(int bit[], int size, int index, int change)
{
    index++;
    while (index < size)
    {
        bit[index] += change;
        index += index & -index;
    }
}
int sum(int bit[], int index)
{
    index++;
    int sum = 0;
    while (index > 0)
    {
        sum += bit[index];
        index -= index & -index;
    }
    return sum;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    pi arr[n];
    vector<int> a;
    rep(i, 0, n)
    {
        cin >> arr[i].f >> arr[i].s;
        a.pb(arr[i].f);
        a.pb(arr[i].s);
    }
    vector<int> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    int cnter = d.size();
    vector<pi> seq[cnter];
    map<pi, int> parents;
    map<pi, int> children;
    rep(i, 0, n)
    {
        arr[i].f = lower_bound(d.begin(), d.end(), arr[i].f) - d.begin();
        arr[i].s = lower_bound(d.begin(), d.end(), arr[i].s) - d.begin();
        seq[arr[i].f].pb(arr[i]);
        seq[arr[i].s].pb(arr[i]);
    }
    int open[cnter + 1], closed[cnter + 1];
    memset(open, 0, sizeof(open));
    memset(closed, 0, sizeof(closed));
    rep(i, 0, cnter)
    {
        for (pi p : seq[i])
        {
            if (p.f == i)
            {
                update(open, cnter + 1, p.s, 1);
            }
            if (p.s == i)
            {
                update(closed, cnter + 1, p.f, 1);
            }
        }
        for (pi p : seq[i])
        {
            if (p.f == i)
                parents[p] = sum(open, cnter - 1) - sum(open, p.s - 1) - 1;
            if (p.s == i)
                children[p] = sum(closed, cnter - 1) - sum(closed, p.f - 1) - 1;
        }
        for (pi p : seq[i])
        {
            if (p.f == i)
            {
            }
            if (p.s == i)
            {
                update(open, cnter + 1, p.s, -1);
            }
        }
    }
    rep(i, 0, n)
    {
        cout << (children[arr[i]] ? 1 : 0) << " ";
    }
    cout << "\n";
    rep(i, 0, n)
    {
        cout << (parents[arr[i]] ? 1 : 0) << " ";
    }
    cout << "\n";

    return 0;
}