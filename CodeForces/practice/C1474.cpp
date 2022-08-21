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
    int nc, n;
    cin >> nc;
    rep(cn, 0, nc)
    {
        cin >> n;
        int a[2 * n];
        bool solution = false;
        rep(i, 0, 2 * n)
        {
            cin >> a[i];
        }
        sort(a, a + 2 * n);
        vi answer;
        rep(r, 0, 2 * n - 1)
        {
            multiset<int> m;
            rep(i, 0, 2 * n)
            {
                m.insert(a[i]);
            }
            answer.clear();
            int target = a[2 * n - 1] + a[r];
            m.insert(target);
            while (m.size() > 1)
            {
                int k = *(next(m.rbegin()));
                m.erase(m.find(k));
                if (m.find(target - k) == m.end())
                {
                    break;
                }
                else
                {
                    m.insert(k);
                    answer.pb(target);
                    answer.pb(target - k);
                    m.erase(m.find(target));
                    m.erase(m.find(target - k));
                    target = k;
                }
            }
            answer.pb(*m.begin());
            if (answer.size() == 2 * n + 1)
                break;
        }
        if (answer.size() == 2 * n + 1)
        {
            cout << "YES" << nL << answer[0] << nL;
            for (int i = 1; i < answer.size(); i += 2)
            {
                cout << answer[i] << " " << answer[i + 1] << nL;
            }
        }
        else
        {
            cout << "NO" << nL;
        }
    }

    return 0;
}