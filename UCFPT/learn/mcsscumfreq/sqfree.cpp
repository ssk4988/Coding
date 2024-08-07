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
    cin.exceptions(cin.failbit);
    vi sq;
    rep(i, 0, 1005){
        sq.pb(i * i);
    }
    int n; cin >> n;
    rep(i, 0, n){
        int a, b; cin >> a >> b; b++;
        auto it1 = lower_bound(all(sq), a);
        auto it2 = lower_bound(all(sq), b);
        int diff = it2 - it1;
        cout << (b - a - diff) << "\n";
    }
    
    return 0;
}
