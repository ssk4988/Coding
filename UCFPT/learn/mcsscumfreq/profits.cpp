#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int n;
    while(true){
        cin >> n;
        if(n == 0) break;
        vi cur(n);
        rep(i, 0, n) cin >> cur[i];
        int best = INT_MIN;
        int mn = 0, pref = 0;
        rep(j, 0, n){
            pref += cur[j];
            best = max(best, pref - mn);
            mn = min(mn, pref);
        }
        cout << best << "\n";
    }
    
    return 0;
}
