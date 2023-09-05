#include <bits/stdc++.h>
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
    int n, q;
    cin >> n >> q;
    vector<array<int, 3>> ivls(n);
    rep(i, 0, n)
    {
        cin >> ivls[i][0] >> ivls[i][1];
        ivls[i][2] = i;
    }
    ivls.pb({int(1e9), int(1e9) + 10, n});
    vector<array<int, 3>> ivlcopy(ivls);
    array<int, 3> best = ivls.back(), curbest = ivls.back();
    sort(all(ivls));
    reverse(all(ivls));
    vector<array<int, 3>> queries(q);
    rep(i, 0, q)
    {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][2] = i;
    }
    sort(all(queries));
    reverse(all(queries));
    int idx = 0, idx1 = 0;
    vi ans(q);
    vi par(n + 1, -1);
    par[n] = n;
    vvi jmp(n + 1, vi(20));
    n++;
    for (auto [l, r, iq] : queries)
    {
        while (idx < n && ivls[idx][0] >= l)
        {
            auto [a, b, iv] = ivls[idx];
            while(idx1 < n && b <= ivls[idx1][0]){
                if(ivls[idx1][1] < best[1]){
                    best = ivls[idx1];
                }
                idx1++;
            }
            jmp[iv][0] = par[iv] = best[2];
            rep(i, 1, 20) jmp[iv][i] = jmp[jmp[iv][i - 1]][i - 1];
            if(b < curbest[1]) curbest = ivls[idx];
            idx++;
        }
        int a = 0;
        if(curbest[1] <= r){
            a++;
            int cur = curbest[2];
            for(int i = 20 - 1; i >= 0; i--){
                if(ivlcopy[jmp[cur][i]][1] <= r) {
                    a += 1 << i;
                    cur = jmp[cur][i];
                }
            }
        }
        
        ans[iq] = a;
    }
    rep(i, 0, q) cout << ans[i] << nL;

    return 0;
}
