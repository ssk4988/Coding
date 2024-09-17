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
    int n,q;
    cin >> n >> q;
    vi a(n + 1);
    vi block(n + 1);
    vi jumps(n + 1);
    vi nex(n + 1);
    nex[n] = n+10;
    block[n] = n+10;
    int k = (int)sqrt(n) + 5;
    rep(i, 0, n)
    {
        block[i] = i / k;
        cin >> a[i];
        a[i] = min(a[i] + i, n);
    }
    auto calc = [&](int i) {
        nex[i] = block[a[i]] != block[i] ? i : nex[a[i]];
        jumps[i] = nex[i] == i ? 0 : 1 + jumps[a[i]];
    };
    for (int i = n - 1; i >= 0; i--)
    {
        calc(i);
    }
    rep(j, 0, q){
        int t, l, r;
        cin >> t >> l;
        l--;
        if(t == 0){
            cin >> r;
            a[l] = min(n, r + l);
            int b = block[l];
            for(int i = min(n, (b + 1) * k)-1; i >= b * k; i--) {
                calc(i);
            }
        }
        else{
            int ans = 1;
            while(a[l] < n){
                if(nex[l] == l) {
                    l = a[l];
                    ans++;
                    continue;
                }
                ans += jumps[l];
                l = nex[l];
            }
            cout << (l + 1) << " " << ans << nL;
        }
    }

    return 0;
}
