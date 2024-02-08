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
    bool zero = false;
    rep(i, 0, n){
        cin >> a[i];
        // if(a[i] == 0) zero = true;
    }
    // if(!zero){
        rep(i, 0, n){
            if(a[i] >= 0) a[i] = -a[i] - 1;
        }
        if(n % 2 == 1){
            int maxdex = -1;
            rep(i, 0, n){
                if(maxdex == -1 || (a[i] < a[maxdex] && a[i] != -1)) maxdex = i;
            }
            if(maxdex == -1){
                maxdex = 0;
            }
            a[maxdex] = -a[maxdex] - 1;
        }
    // }
    rep(i, 0, n){
        cout << a[i] << " ";
    }
    cout << nL;
    
    return 0;
}
