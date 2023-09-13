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
        int l, r; cin >> l >> r;
        // test 1, 1 and 2, 2
        if(l == r){
            bool works = false;
            for(ll i = 2; i * i <= l; i++){
                if(l % i == 0){
                    works = true;
                    int other = l / i;
                    int a = other, b = l - other;
                    cout << a << " " << b << nL;

                    break;
                }
            }
            if(!works){
                cout << "-1\n";
            }
            continue;
        }
        int a = (l + 1) / 2 * 2;
        int b = 2;
        a -= 2;
        while(a <= 0) a += 2;
        if(a > 0 && b > 0 && a + b >= l && a + b <= r){
            cout << a << " " << b << nL;
        }
        else cout << "-1\n";
    }
    
    return 0;
}