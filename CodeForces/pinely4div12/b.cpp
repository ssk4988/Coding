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
        int n; cin >> n;
        vi b(n);
        rep(i, 1, n){
            cin >> b[i];
        }
        vi a(n);
        a[0] = b[1];
        a[n-1] = b[n-1];
        rep(i, 1, n-1){
            a[i] = b[i] | b[i+1];
        }
        bool works = true;
        rep(i, 1, n){
            if((a[i-1] & a[i]) != b[i]) works = false;
        }
        if(!works) cout << "-1\n";
        else{
            rep(i, 0, n) cout << a[i] << " ";
            cout << "\n";
        }
    }
    
    return 0;
}
