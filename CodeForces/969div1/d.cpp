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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, q, k;
        cin >> n >> q >> k;
        vi o(n);
        vi t(n); // 1 if too big
        vi a(n);
        rep(i, 0, n)
        {
            cin >> o[i];
            int other = k / o[i];
            t[i] = o[i] > other;
            a[i] = (t[i] ? other : o[i]);
        }
        int V = 0;
        while (V * V <= k)
            V++;
        V += 5;
        vi over(V), under(V);
        int block = sqrt(n) + 20;
        vector<array<int, 4>> queries;
        rep(i, 0, q)
        {
            int l, r;
            cin >> l >> r;
            l--;
            queries.push_back({l / block, r, l, i});
        }
        sort(all(queries));
        vi ans(q);
        int L = 0, R = 0;

        auto oper = [&](int idx, int add) -> void
        {
            if (t[idx])
            {
                over[a[idx]] += add ? 1 : -1;
            }
            else
                under[a[idx]] += add ? 1 : -1;
        };
        for (auto [bl, r, l, qidx] : queries)
        {
            while (R < r)
            {
                oper(R, 1);
                R++;
            }
            while (r < R)
            {
                R--;
                oper(R, 0);
            }
            while (L < l)
            {
                oper(L, 0);
                L++;
            }
            while (l < L)
            {
                L--;
                oper(L, 1);
            }
            int cntover = 0, cntunder = 0, prv = 0; // prv 0 is under, 1 is over
            int res = 0;
            rep(i, 0, sz(over))
            {
                cntover += over[i];
                cntunder += under[i];
                if (prv == 1 && max(cntover, cntunder) > 0)
                {
                    res++;
                    cntover--;
                    cntunder++;
                }
                while (true)
                {
                    int rem = max(0, min(cntover, cntunder));
                    cntover -= rem, cntunder -= rem;
                    if (prv == 0 && cntover > 0)
                    {
                        prv = 1;
                        cntover--;
                    }
                    if (prv == 1 && cntunder > 0)
                    {
                        prv = 0;
                        cntunder--;
                    }
                    if (cntover <= 1)
                        break;
                    rem = max(cntover / 2 - 4, 1);
                    res += rem;
                    cntover -= rem;
                    cntunder += rem;
                }
            }
            if (prv == 1 && max(cntover, cntunder) > 0)
            {
                res++;
                cntover--;
                cntunder++;
            }
            ans[qidx] = res;
        }
        rep(i, 0, q)
        {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
