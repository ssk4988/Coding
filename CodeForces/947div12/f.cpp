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
    int n; cin >> n;
    vi mask(1 << n);
    rep(i, 1, sz(mask)){
        cin >> mask[i];
    }
    vvi masks(n+1, vi(1 << n));
    masks[0] = mask;
    masks[0][0] = 1;
    vi ans;
    auto calc = [&](int used, int curmask, auto &&calc) -> void {
        if(used == n){
            if(masks[used][0] & 1) ans.pb(curmask);
            return;
        }
        // set this bit off
        int left = n - used - 1;
        rep(i, 0, 1 << left){
            int remmask = i << (used+1);
            masks[used+1][remmask] = masks[used][remmask] & masks[used][remmask | (1 << used)];
        }
        // cout << used << " " << curmask << ":\n";
        rep(i, 0, 1 << left){
            int remmask = i << (used+1);
            // cout << remmask << " " << masks[used+1][remmask] << "\n";
        }
        calc(used+1, curmask, calc);
        // set this bit on
        rep(i, 0, 1 << left) {
            int remmask = i << (used+1);
            masks[used+1][remmask] = masks[used][remmask] & (masks[used][remmask | (1 << used)] >> 1);
        }
        // cout << used << " " << curmask << ":\n";
        rep(i, 0, 1 << left){
            int remmask = i << (used+1);
            // cout << remmask << " " << masks[used+1][remmask] << "\n";
        }
        calc(used+1, curmask ^ (1 << used), calc);
    };
    calc(0, 0, calc);
    sort(all(ans));
    cout << sz(ans) << "\n";
    for(int i : ans) cout << i << "\n";

    return 0;
}
