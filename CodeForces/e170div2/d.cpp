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
    int n, m; cin >> n >> m;
    vi ans{0};
    rep(i, 0, n){
        int r; cin >> r;
        if(r == 0) {
            partial_sum(all(ans), begin(ans));
            ans.pb(0);
            for(int i = sz(ans)-1; i > 0; i--) ans[i] = max(ans[i], ans[i-1]);
            for(int i = sz(ans)-1; i > 0; i--) ans[i] -= ans[i-1];
        } else if(r > 0){
            ans[0]++;
            if(r <= sz(ans)) ans[sz(ans)-r]--;
        } else {
            r *= -1;
            if(r < sz(ans)) ans[r]++;
        }
    }
    partial_sum(all(ans), begin(ans));
    cout << *max_element(all(ans)) << "\n";
    
    return 0;
}