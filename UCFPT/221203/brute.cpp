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
    int t;
    cin >> n >> t;
    vi h(n);
    vector<queue<pi>> q;
    q.pb(queue<pi>());
    rep(i, 0, n)
    {
        cin >> h[i];
        q[0].push({i, h[i]});
    }
    for (int j = 0; j < t; j++)
    {
        for (int i = q.size() - 1; i >= 0; i--)
        {
            q[i].front().s--;
            if (q[i].front().s == 0)
            {
                pi k = q[i].front();
                q[i].pop();
                if (i + 1 >= q.size())
                {
                    q.pb(queue<pi>());
                }
                k.s = h[k.f];
                q[i + 1].push(k);
            }
        }
    }
    for(int i = q.size() - 1; i >= 0; i--){
        for(int j = 0; j < q[i].size(); j++){
            cout << (i + 1) << nL;
        }
    }

    return 0;
}