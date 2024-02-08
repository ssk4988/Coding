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

const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n), b(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n) cin >> b[i];
        sort(all(a));
        sort(all(b));
        reverse(all(a));
        reverse(all(b));
        int pnt = 0;
        ll ways = 1;
        rep(i, 0, n){
            while(pnt < n && a[pnt] > b[i]){
                pnt++;
            }
            int w = pnt - i;
            if(w <= 0) ways = 0;
            ways = mod(ways * w);
        }
        cout << ways << "\n";
    }
    
    return 0;
}
