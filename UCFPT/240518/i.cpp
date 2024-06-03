#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
using a3 = array<int, 3>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vector<pii> best;
        vector<pii> mk;
        vi p(n);
        rep(i, 0, n)
        {
            int v;
            cin >> v;
            v--;
            p[i] = v;
            mk.emplace_back(v, -1);
            int idx = lower_bound(all(best), mk.back()) - best.begin();
            if (idx == sz(best))
                best.resize(idx + 1);
            if (idx)
                mk.back().s = best[idx - 1].s;
            best[idx] = pii{v, sz(mk) - 1};
        }
        vi lis;
        int cur = best.back().s;
        int last = cur, lim = p[cur];
        vi used(n);
        while (cur != -1)
        {
            lis.push_back(cur);
            used[cur] = true;
            cur = mk[cur].s;
        }
        reverse(all(lis));
        // for (int i : lis)
        //     cout << i << " ";
        // cout << "\n";
        vi left;
        vi ord;
        int mx = -1;
        priority_queue<pii, vii, greater<pii>> pq;
        rep(i, 0, n)
        {
            if (used[i])
            {
                while(sz(pq) && pq.top().f < p[i]){
                    auto [v, idx] = pq.top(); pq.pop();
                    used[idx] = true;
                    ord.pb(idx);
                }
                ord.pb(i);
                mx = p[i];
            }
            else if (p[i] < mx)
                ord.pb(i), used[i] = true;
            else
                pq.push({p[i], i});
        }
        while(sz(pq)){
            auto [v, idx] = pq.top(); pq.pop();
            ord.pb(idx);
        }
        // rep(i, 0, n)
        // {
        //     if (!used[i])
        //         left.pb(i);
        // }
        // sort(all(left), [&](int a, int b) -> bool
        //      { return p[a] < p[b]; });
        for (int i : ord)
            cout << i + 1 << " ";
        // for (int i : left)
        //     cout << i + 1 << " ";
        cout << "\n";
    }

    return 0;
}
