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

ld eps = 0.002;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(50, 120);
    uniform_int_distribution<int> t(0, n - 1);
    int attempts = 0;
    pair<ld, pll> rat{1, {-1, -1}};
    vvi perms;
    {
        vi perm(n);
        iota(all(perm), 0);
        do
        {
            perms.pb(perm);
        } while (next_permutation(all(perm)));
    }
    cout << sz(perms) << endl;
    while (true)
    {
        attempts++;
        if (attempts % 100000 == 0)
        {
            shuffle(all(perms), rng);
            rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
            cout << attempts << " " << fixed << setprecision(8) << rat.f << " " << rat.s.f << " " << rat.s.s << endl;
        }
        int k = dist(rng);
        ll best = LLONG_MIN, worst = LLONG_MAX;
        vvi ps(n);
        rep(i, 0, k * n)
        {
            while (true)
            {
                int tm = t(rng);
                if (sz(ps[tm]) >= k)
                    continue;
                ps[tm].pb(i);
                break;
            }
        }
        // ll tot = 0;
        for (auto &perm : perms)
        {
            vector<vl> dp(n, vl(k, -1)), pref(n, vl(k, -1));
            auto go = [&](int used, int idx, auto &&go, auto &&gop) -> ll
            {
                ll &ans = dp[used][idx];
                if (ans != -1)
                    return ans;
                if (used == n - 1)
                    return ans = 1;
                ans = 0;
                int nidx = lower_bound(all(ps[perm[used + 1]]), ps[perm[used]][idx]) - ps[perm[used + 1]].begin();
                return ans = gop(used + 1, nidx, go, gop);
            };
            auto gop = [&](int used, int idx, auto &&go, auto &&gop) -> ll
            {
                if (idx == k)
                    return 0;
                ll &ans = pref[used][idx];
                if (ans != -1)
                    return ans;
                return ans = go(used, idx, go, gop) + gop(used, idx + 1, go, gop);
            };
            ll ans = gop(0, 0, go, gop);
            best = max(best, ans), worst = min(worst, ans);
            // tot += ans;
            if (ld(abs(best - worst)) / best >= eps)
                break;
        }
        // cout << n << " k: " << k << " tot: " << tot << "\n";
        rat = min({ld(abs(best - worst)) / best, {worst, best}}, rat);
        if (rat.f >= eps)
            continue;
        cout << attempts << " " << rat.f << " " << best << " " << worst << "\n";
        cout << k << "\n";
        rep(i, 0, n)
        {
            rep(j, 0, k) cout << ps[i][j] + 1 << " ";
            cout << endl;
        }
        break;
    }

    return 0;
}
