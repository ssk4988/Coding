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
    int n, m ,k; cin >> n >> m >> k;
    vi a(n), b(m);
    rep(i, 0, n){
        cin >> a[i];
    }
    int apnt = 0, bpnt = 0;
    rep(i, 0, m){
        cin >> b[i];
    }
    sort(all(a));
    sort(all(b));
    int ans = 0;
    while(apnt < n && bpnt < m){
        if(abs(a[apnt] - b[bpnt]) <= k){
            ans++;
            apnt++;
            bpnt++;
            continue;
        }
        if (a[apnt] < b[bpnt]){
            apnt++;
        }
        else{
            bpnt++;
        }
    }
    cout << ans << nL;
    
    return 0;
}
