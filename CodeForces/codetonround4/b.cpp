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
        if(n % 2 == 0){
            cout << "-1\n";
            continue;
        }
        vi moves;
        while(n > 1){
            int m1 = (n + 1) / 2, m2 = (n - 1) / 2;
            if(m1 % 2 == 0){
                moves.pb(2);
                n = m2;
            }
            else{
                moves.pb(1);
                n = m1;
            }
        }
        if(n != 1){
            cout << "-1\n";
        }
        else{
            reverse(all(moves));
            cout << sz(moves) << nL;
            rep(i, 0, sz(moves)){
                cout << moves[i] << " ";
            }
            cout << nL;

        }
    }
    
    return 0;
}
