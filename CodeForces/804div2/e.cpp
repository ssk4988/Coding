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
const int LIM = 5e6;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vi lp(LIM+1), primes;
    rep(i, 2, LIM + 1) {
        if (lp[i] == 0) primes.push_back(lp[i] = i);
        for (int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vi has(m+1);
        rep(i, 0, n) has[a[i]] = true;
        int ans = m;
        if(*max_element(all(a)) == 1) ans = 0;
        vi mx(m+1, 1);
        int mnconsider = 0;
        rep(i, 2, m+1){
            int left = i;
            mx[i] = lp[i];
            while(left > 1){
                if(has[i]) mnconsider = max(mnconsider, lp[left]);
                left /= lp[left];
            }
        }
        vi lower(m+1);
        rep(i, 0, m+1) if(has[i]) lower[mx[i]]++;
        int l = 0;
        rep(y, 2, m+1){
            for(int x = y; x <= m; x += y){
                if(has[x]) lower[mx[x]]--;
                if(x == y) mx[x] = x;
                else mx[x] = max(mx[x], min(y, mx[x/y]));
                if(has[x]) lower[mx[x]]++;
            }
            while(l <= m && lower[l] == 0) l++;
            if(y >= mnconsider) ans = min(ans, y - l);
        }
        cout << ans << "\n";
    }    
    
    return 0;
}
