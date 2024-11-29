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
        int m; cin >> m;
        vi s(m);
        rep(i, 0, m) cin >> s[i];
        sort(all(s));
        reverse(all(s));
        vvi divs(n+1);
        rep(i, 1, n+1){
            for(int j = 2 * i; j <= n; j += i) divs[j].pb(i);
        }
        vi a(n+1);
        bool works = true;
        rep(i, 1, n+1){
            vi seen(25);
            for(int j : divs[i]) seen[a[j]] = 1;
            int mex = 0;
            while(seen[mex]) mex++;
            a[i] = mex;
            if(mex >= m) works = false;
        }
        if(!works){
            cout << "-1\n";
            continue;
        }
        rep(i,1,n+1) cout << s[a[i]] << " ";
        cout << "\n";
    }
    
    return 0;
}
