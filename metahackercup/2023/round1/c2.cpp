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
    int maxn = 4000100;
    vvi adj(maxn + 1);
    vvi radj(maxn + 1);
    vi type(maxn + 1);
    type[1] = 1;
    rep(i, 1, maxn + 1)
    {
        for (int j = i * 2; j < sz(type); j += i)
            type[j] = type[j] ^ type[i];
    }
    rep(i, 1, maxn + 1)
    {
        for (int j = i, p = 1; j < sz(type); j += i, p++)
        {
            if (type[p])
            {
                adj[i].pb(j);
                radj[j].pb(i);
            }
        }
    }
    int divsum = 0, mx = 0, mx1 = 0;
    rep(i, 1, maxn + 1)
    {
        int divcnt = 0;
        // rep(j, 1, i + 1){
        //     if(i % j == 0) divcnt++;
        // }
        divsum += sz(adj[i]);
        mx = max(mx, sz(adj[i]));
        mx1 = max(mx1, sz(radj[i]));
        // cout << i << " " << type[i] << " " << sz(adj[i]) << nL;
    }
    // cout << divsum << nL;
    cout << mx << " " << mx1 << nL;
    // rep(i, 1, 100){
    //     cout << i << " " << sz(adj[i]) << nL;
    // }

    int nc = 0;
    // cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        string str;
        cin >> str;
        vector<bool> res(n);
        rep(i, 0, n) res[i] = str[i] == '1';
        int q;
        cin >> q;
        vector<bool> updates(n);
        vl cont(n);
        vi ison(n);
        rep(i, 0, n){
            if(res[i]){
                ison[i] = ison[i] ^ 1;
                cont[i] = q;
            }
        }
        rep(i, 0, q)
        {
            int idx;
            cin >> idx;
            idx--;
            if(ison[idx]){
                cont[idx] -= q - i;
            }
            else cont[idx] += q - i;
            ison[idx] = ison[idx] ^ 1;
            // updates[idx] = updates[idx] ^ 1;
        }
        rep(i, 0, n){
            ll a1 = 0;
            bool on = 0;
            for(int j : radj[i + 1]){
                a1 += (on ? cont[j - 1] : q - cont[j - 1]);
                on = on ^ 1;
            }
        }
        rep(i, 0, n)
        {
            if (updates[i])
            {
                for (int j : adj[i + 1])
                {
                    if (j - 1 < n)
                        res[j - 1] = res[j - 1] ^ 1;
                    else
                        break;
                }
            }
        }

        ll ans = 0;
        rep(i, 0, n)
        {
            if (res[i])
            {
                ans++;
                for (int j : adj[i + 1])
                {
                    if (j - 1 < n)
                        res[j - 1] = res[j - 1] ^ 1;
                    else
                        break;
                }
            }
        }
        cout << "Case #" << (cn + 1) << ": " << ans << nL;
    }
    return 0;
}
