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
        ll a, b, c, d; cin >> a >> b >> c >> d;
        if(a * b * 2 <= c * d){
            bool found = false;
            rep(i, a + 1, c + 1){
                if(a * b * 2 % i != 0) continue;
                int j = a * b * 2 / i;
                if(j == b) j *= 2;
                if(j > b && j <= d){
                    cout << i << " " << j << "\n";
                    found = true;
                    break;
                }
            }
            if(!found)
            cout << "-1 -1\n";
            // assert(found);
            // if(!found)
            // cout << "not found\n";
        }
        else{
            cout << "-1 -1\n";
        }
    }
    
    return 0;
}