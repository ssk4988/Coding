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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){ 
        int n; cin >> n;
        vi a(n);
        map<int, int> freq;
        rep(i, 0, n) {
            cin >> a[i];
            freq[a[i]]++;
        }
        vi suff;
         ord;
        for(int i = n-1; i >= 0; i--) {
            if(sz(suff) == 0 || a[i] <= suff.back()) {
                suff.pb(a[i]);
            }
            ord.pb(a[i]);
        }
        vi res;
        int p1 = 0, p2 = 0;
        bool useord = false;
        while(sz(res) < n) {
            if(p2 == sz(suff) || (p1 < sz()))
        }
        suff.insert(end(suff), all(ord));
        sort(all(suff));
        for(int a : suff) cout << a << " ";
        cout << "\n";
    }    
    
    return 0;
}
