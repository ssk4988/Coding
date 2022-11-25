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
    string str;
    cin >> str;
    int n = str.length();
    int a[n];
    rep(i, 0, n){
        a[i] = str[i] - 'a';
    }
    ll ans = 0;
    rep(t, 0, 26){
        bool seen[26];
        int curdiff = 0;
        memset(seen, false, sizeof seen);
        rep(i, 0, n){
            if(a[i] == t){
                if(seen[t]){
                    ans += curdiff - 1;
                }
                curdiff = 0;
                memset(seen, false, sizeof seen);
            }
            if(!seen[a[i]]){
                seen[a[i]] = true;
                curdiff++;
            }
        }
        if(seen[t]){
            ans += curdiff - 1;
        }
    }
    cout << ans << nL;
    
    return 0;
}