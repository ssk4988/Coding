#include <bits/stdc++.h>
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
    rep(mid, 1, 100000){
        ll v = mid * (mid + 1) / 2;
        ll cnt = 0;
        for(ll i = 1; i * i <= v; i++){
            if(v % i == 0){
                cnt++;
                ll other = v / i;
                if(other != i) cnt++;
            }
        }
        if(cnt >= 500){
            cout << v << nL;
            break;
        }
    }
    
    
    return 0;
}
