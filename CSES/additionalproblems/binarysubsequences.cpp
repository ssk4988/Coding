#pragma GCC optimize("Ofast")
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

const int oo = 1e9;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;
    vvi ls(n + 1); // all b for given a
    for (int i = n; i > n - i; i--)
        ls[i].pb(n - i);
    for (int a = n; a >= 1; a--)
    {
        sort(all(ls[a]));
        ls[a].erase(unique(all(ls[a])), ls[a].end());
        while(sz(ls[a]) && (ls[a].back() == a)) ls[a].pop_back();
        for (int b : ls[a])
        {
            // if(a == b) continue;
            if (b == 0)
                continue;
            // if (a == b + 1 && b > 1)
            //     continue;
            int c = a % (b + 1);
            ls[max(c, b)].pb(min(c, b));
        }
    }
    vvi ans(n+1);
    for(int a = 1; a <= n; a++){
        ans[a].resize(sz(ls[a]));
        rep(j, 0, sz(ls[a])){
            int b = ls[a][j];
            int& res = ans[a][j];
            // if(a == b) res = oo;
            // else 
            if (b == 0) res = a;
            // else if(a == b + 1 && b > 1) res = oo;
            else if(a == 2 && b == 1) res = 2;
            else{
                int c = a % (b + 1);
                int idx = lower_bound(all(ls[max(c, b)]), min(c, b)) - ls[max(c, b)].begin();
                if(idx == sz(ls[max(c, b)])) res = oo;
                else res = (a - c) / (b+1) + ans[max(c, b)][idx];
            }
        }
    }

    pi best = {n, 0};
    int bestans = n;
    for (int i = n; i > n - i; i--)
    {
        int idx = lower_bound(all(ls[max(i, n-i)]), min(i, n-i)) - ls[max(i, n-i)].begin();
        if(idx == sz(ls[max(i, n-i)])) continue;
        if (ans[i][idx] < bestans)
            best = {i, n - i}, bestans = ans[i][idx];
    }
    int cur = 0;
    while (best.f != 0)
    {
        int c = best.f % (best.s + 1);
        int d = (best.f - c) / (best.s + 1);
        rep(i, 0, d) cout << cur;
        cur = 1 - cur;
        best.f = c;
        if (best.f < best.s)
            swap(best.f, best.s);
    }
    cout << "\n";

    return 0;
}
