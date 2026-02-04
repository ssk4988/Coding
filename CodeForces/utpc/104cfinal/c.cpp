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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int lim = 1e7+10;
bool prime[lim];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(prime, 1, sizeof prime);
    prime[0] = prime[1] = 0;
    rep(i, 2, lim) {
        if(ll(i) * i >= lim) continue;
        if(!prime[i]) continue;
        for(int j = i*i; j < lim; j += i) prime[j] = 0;
    }
    int a, b; cin >> a >> b;
    int ans = 0;
    int c = b;
    while(c < 1e7) {
        ans += prime[c];
        c += a;
    }
    cout << ans << "\n";
    

    
    return 0;
}
