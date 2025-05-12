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
    int n; cin >> n;
    auto query = [&](int l, int r) -> ll {
        cout << "? " << l+1 << " " << r+1 << endl;
        ll inv; cin >> inv;
        if(inv == 0) exit();
        return inv;
    };
    // 
    vi ord{0};
    ll inv = query(0, 1);
    rep(i,1,n) {
        ll inv2 = query(0, i);
        if(1 < i-1) inv2 = query(1, i-1);
        ll invend = n-2-i;
        ll cnt = inv2
    }
    
    return 0;
}
