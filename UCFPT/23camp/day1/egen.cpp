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
using vvl = vector<vl>;

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
    int n = 10;
    int upb = n + 1;
    rep(i, 1, upb){
        rep(j, i + 1, upb){
            rep(k, j + 1, upb){
                bool works = true;
                rep(l, 0, 15){
                    vi v(4, l);
                    v[2] %= k;
                    v[3] %= k;
                    v[3] %= j;
                    v[1] %= j;
                    v[0] %= i;
                    v[1] %= i;
                    v[2] %= i;
                    v[3] %= i;
                    if(v[0] == v[1] && v[1] == v[2] && v[2] == v[3]){
                        
                    }
                    else{
                        works = false;
                        break;
                    }
                }
                if(works){
                    ans++;
                    cout << i << " " << j << " " << k << nL;
                }
            }
        }
    }
    cout << ans << nL;
    return 0;
}
