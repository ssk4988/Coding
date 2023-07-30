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
    int ans = 0;
    for(int i = 100; i < 1000; i++){
        for(int j = 100; j < 1000; j++){
            int k = i * j;
            int k1 = k;
            vi str;
            while(k){
                str.pb(k % 10);
                k /= 10;
            }
            vi str1(str);
            reverse(all(str1));
            if(str == str1) ans = max(ans, k1);
        }
    }
    cout << ans << nL;
    
    return 0;
}
