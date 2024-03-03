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
    int n = 100001;
    int k = 2 * n / 3 + 1;
    cout << k << endl;
    vi known(n), t(n);
    for(int i = 0; i < n; i += 3){
        known[i] = t[i] = true;
    }
    t[n-1] = true;
    known[n-1] = true;
    auto guess = [&](int x) -> int {
        if(!known[x]){
            int x1 = x / 3 * 3 + 3 - (x % 3);
            if(!known[x1]) t[x1] = true;
            t[x] = !t[x1];
            known[x] = known[x1] = true;
        }
        if(t[x]){
            // if(x % 3 == 0) return 2 * x / 3 + 1;
            return (2 * (x / 3) + 1 + (x % 3 != 0));
        }
        else return -1;
    };
    while(true){
        int x; cin >> x;
        if(x == -1) {
            break;
        }
        int res = guess(x);
        cout << res << endl;
    }
    rep(i, 0, n){
        guess(i);
    }
    rep(i, 0, n){
        if(t[i]) cout << i << endl;
    }
    
    return 0;
}