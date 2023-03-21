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
    cout << 1 << nL;
    cout << 50000 * 996 << nL;
    rep(i, 1, 50001){
        rep(j, 0, 996){
            cout << fixed << setprecision(2) << (i / 100.0) << nL;
        }
    }
    int numq = 5;
    cout << 2 << " " << numq << nL;
    rep(i, 0, numq){
        cout << fixed << setprecision(2) << ((i + 1) / 100.0) << nL;
    }
    
    return 0;
}
