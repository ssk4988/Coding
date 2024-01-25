#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n), b(n);
    rep(i, 0, n){
        cin >> a[i] >> b[i];
    }
    int lo = 0, hi = n;
    while(lo < hi){
        int mid = lo + (hi - lo + 1) / 2;
        bool found = false;
        rep(i, 0, n){
            if(i + mid > n) break;
            if(min(b[i], b[i + mid - 1]) - max(a[i], a[i + mid - 1]) + 1 >= mid) found = true;
        }
        if(found) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";

    return 0;
}
