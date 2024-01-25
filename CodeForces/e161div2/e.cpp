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
        ll x; cin >> x;
        ll b = 1;
        int p = 0;
        vl a;
        a.push_back(0);
        a.push_back(0);
        while(b * 2 <= x){
            a.push_back(p + 1);
            a.push_back(0);
            b <<= 1;
            p++;
        }
        a[sz(a) - 2] = 1000;

        x -= b;
        b = 2;
        for(int p1 = 1; p1 < p; p1++, b <<= 1){
            if(x & b){
                a[p1 * 2 - 1] = 1000 - p1;
            }
        }
        if(x & 1){
            a[0] = 1001;
        }
        // if(a[0]) a[0]++;
        int cnt = 0;
        for(auto x : a){
            if(x) cnt++;
        }
        cout << cnt << "\n";
        for(auto x : a){
            if(x){
                cout << x << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
