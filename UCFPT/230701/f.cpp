#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    freopen("army.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    auto sum = [](ll k)->ll{
        return k * (2 * k + 1) * (k + 1) / 6;
    };
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll lo = 0, hi = 1442250;
        ll n; cin >> n;
        while(lo < hi){
            ll mid = lo + (hi - lo) / 2;
            if(sum(mid) >= n) hi = mid;
            else lo = mid + 1;
        }
        ll row = lo;
        lo = 1, hi = 2 * row - 1;
        while(lo < hi){
            ll mid = lo + (hi - lo) / 2;
            ll v;
            if(mid <= row) v = mid * (mid + 1) / 2;
            else v = row * row - (2 * row - 1 - mid) * (2 * row - 1 - mid + 1) / 2;
            if(v + sum(row - 1) >= n) hi = mid;
            else lo = mid + 1;
        }
        ll reps = (row - 1) * (row - 1) + lo;
        cout << "Case " << (cn + 1) << ": " << reps << "\n";
    }

}
