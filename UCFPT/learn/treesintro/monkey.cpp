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
    int nc; cin >> nc;
    string str;
    getline(cin, str);
    rep(cn, 0, nc){
        getline(cin, str);
        int idx = 0;
        auto solve = [&](auto &&solve) -> ll {
            if(idx == sz(str) || str[idx] == ']') return 1;
            idx++;
            ll l = solve(solve), r = solve(solve);
            assert(str[idx] == ']');
            idx++;
            return 2 * l / __gcd(l, r) * r;
        };
        cout << (cn + 1) << " " << solve(solve) << "\n";
    }
    
    return 0;
}
