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
    rep(cn, 0, nc) {
        int n; cin >> n;
        int nonzero = 0;
        vi a(n);
        int first0 = -1;
        rep(i, 0, n) {
            cin >> a[i];
            if(a[i]) nonzero++;
            else if(first0 == -1) first0 = i;
        }
        if(nonzero == n){
            cout << n << "\n";
            continue;
        }
        set<int> seen;
        int mex = 0;
        int cand = 0;
        for(int i = n-1; i >= 0; i--) {
            if(i == first0) {
                seen.insert(a[i]);
                cand++;
            } else if(a[i] > 0 && a[i] >= mex) {
                seen.insert(a[i]);
                cand++;
            }
            while(seen.count(mex)) mex++;
        }
        cout << max(cand, nonzero) << "\n";
    }
    
    return 0;
}
