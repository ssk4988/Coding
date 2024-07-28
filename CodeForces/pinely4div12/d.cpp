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
        if(n == 1){
            cout << "1\n1\n";
        } else if(n == 2){
            cout << "2\n1 2\n";
        } else if(n == 3){
            cout << "2\n1 2 2\n";
        } else if(n == 4){
            cout << "3\n1 2 2 3\n";
        } else if (n == 5){
            cout << "3\n1 2 2 3 3\n";
        } else{
            cout << 4 << "\n";
            rep(i, 1, n+1){
                cout << (1 + (i % 4)) << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
