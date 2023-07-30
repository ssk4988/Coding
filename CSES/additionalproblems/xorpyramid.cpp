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
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi num2(n + 1);
    rep(i, 1, n + 1){
        int v = i;
        while(v % 2 == 0){
            num2[i]++;
            v /= 2;
        }
    }
    rep(i, 1, n + 1) num2[i] += num2[i - 1];
    int ans = 0;
    rep(i, 0, n){
        ans ^= (num2[n - 1] - num2[i] - num2[n - 1 - i] > 0 ? 0 : 1) * a[i];
    }
    cout << ans << nL;
    
    return 0;
}
