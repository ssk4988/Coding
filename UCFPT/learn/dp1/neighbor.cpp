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
#define maxN 1005

pair<int, vi> dp[maxN];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        int a[n];
        rep(i, 0, n){
            dp[i] = mp(0, vi());
        }
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n){
            pair<int, vi> best = i - 2 >= 0 ? dp[i - 2] : mp(0, vi());
            best.f += a[i];
            best.s.pb(i);
            pair<int, vi> prev = i - 1 >= 0 ? dp[i - 1] : mp(0, vi());
            dp[i] = prev.f > best.f || (prev.f == best.f && prev.s < best.s) ? prev : best;
        }
        cout << "Case #" << (cn + 1) << ": " << dp[n - 1].f << " : ";
        // for(int i = 0; i < dp[n - 1].s.size(); i++){
        //     cout << dp[n - 1].s[i];
        //     if(i + 1 < dp[n - 1].s.size()){
        //         cout << " ";
        //     }
        //     else{
        //         cout << nL;
        //     }
        // }
        for(auto i : dp[n - 1].s){
            cout << i << " ";
        }
        cout << nL;     
    }
    
    return 0;
}