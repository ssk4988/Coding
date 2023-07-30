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
    int numbits = 55;
    vl bitsum(numbits);
    bitsum[0] = 1;
    rep(i, 1, numbits){
        bitsum[i] = bitsum[i - 1] * 2 + ((1LL) << i);
    }
    ll n; cin >> n; n++;
    auto solve = [&](ll v)->ll{
        ll ans = 0, ones = 0;
        for(int i = numbits - 1; i >= 0; i--){
            if(v & (1LL << i)){
                ans += (i ? bitsum[i - 1] : 0) + ones * (1LL << i);
                ones++;
            }
        }
        return ans;
    };
    // rep(i, 1, 12){
    //     cout << i << " " << solve(i) << nL;
    // }
    cout << solve(n) << nL;
    
    return 0;
}