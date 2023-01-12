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
    nex[n] = n;
    block[n] = n;
    int k = (int)sqrt(n);
    rep(i, 0, n)
    {
        block[i] = i / k;
        cin >> a[i];
        a[i] = min(a[i], n - i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        jumps[i] = 1 + (block[i + a[i]] == block[i] ? jumps[i + a[i]] : 0);
        nex[i] = block[i + a[i]] != block[i] ? i + a[i] : nex[i + a[i]];
    }
    rep(j, 0, q){
        int t, l, r;
        cin >> t >> l;
        l--;
        if(t == 0){
            cin >> r;
            a[l] = min(r, n - l);
            for(int i = l; i >= block[l] * k; i--){
                jumps[i] = 1 + (block[i + a[i]] == block[i] ? jumps[i + a[i]] : 0);
                nex[i] = block[i + a[i]] != block[i] ? i + a[i] : nex[i + a[i]];
            }
        }
        else{
            int ans = 0, pre = -1;
            while(l < n){
                ans += jumps[l];
                pre = l;
                l = nex[l];
            }
            cout << (pre + 1) << " " << ans << nL;
        }
    }

    return 0;
}