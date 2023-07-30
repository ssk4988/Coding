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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        int cntf = 0, cntb = 0;
        rep(i, 0, n){
            if(cntf >= k && a[i] == a[n - 1]) cntb++;
            if(a[i] == a[0]) cntf++;
        }
        bool works;
        if(a[0] == a[n - 1]){
            works = cntf >= k;
        }
        else{
            works = cntf >= k && cntb >= k;
        }
        cout << (works ? "YES": "NO") << nL;
    }
    
    return 0;
}