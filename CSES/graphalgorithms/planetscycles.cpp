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
    int c[n];
    vvi p;
    int ans[n];
    memset(ans, 0, sizeof ans);
    p.assign(n, {});

    rep(i, 0, n)
    {
        cin >> c[i];
        c[i]--;
        p[c[i]].pb(i);
    }
    rep(i, 0, n)
    {
        if (!ans[i])
        {
            int a = i;
            int b = i;
            do
            {
                a = c[a];
                b = c[c[b]];
            } while (a != b);
            a = i;
            while (a != b)
            {
                a = c[a];
                b = c[b];
            }
            int l = 0;
            do
            {
                a = c[a];
                l++;
            } while (a != b);
            do
            {
                ans[a] = l;
                a = c[a];
            } while (a != b);
            deque<pi> q;
            q.pb(mp(a, l));
            while (q.size())
            {
                pi m = q.front();
                q.pop_front();
                ans[m.f] = m.s;
                for (int i : p[m.f])
                {
                    if (!ans[i])
                        q.pb(mp(i, m.s + 1));
                }
            }
        }
        cout << ans[i] << " ";
    }
    cout << nL;

    return 0;
}