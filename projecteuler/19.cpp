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
    int d = 1 % 7;
    vi months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ans = 0;
    rep(i, 0, 101){
        rep(j, 0, 12){
            if(d == 0 && i) ans++; 
            d = (d + months[j]) % 7;
            if(j == 1 && (i % 4 == 0 && (i == 0 || i % 400 != 0))){
                d = (d + 1) % 7;
            }
        }
    }
    cout << ans << nL;
    
    return 0;
}
