#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    ll cursum = 0, window = 0;;
    vpl windows;
    rep(i, 0, k){
        cursum += a[i];
        window += (i + 1) * a[i];
    }
    windows.pb({window, 0});
    int idx = 0;
    while(idx + k < n){
        window -= cursum;
        cursum -= a[idx];
        cursum += a[idx + k];
        window += k * a[idx + k];
        idx++;
        windows.pb({window, idx});
    }
    sort(all(windows));
    for(auto [w, i] : windows){
        cout << (i + 1) << " " << w << "\n";
    }
}
