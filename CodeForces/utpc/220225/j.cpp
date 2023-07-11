#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<ll> ans(n);
    int cur = n - 1;
    auto invert = [](int k, int hbit)->int{
        return (~k) & ((1 << (hbit + 1)) - 1);
    };
    while(cur > 0){
        int hbit = -1;
        for(int i = 25; i >= 0 && hbit == -1; i--){
            if(cur & (1 << i)){
                hbit = i;
            }
        }
        int nex = invert(cur, hbit) - 1;
        while(true){
            int icur = invert(cur, hbit);
            if(cur < icur) break;
            ans[cur] = icur;
            ans[icur] = cur;
            cur--;
        }
        cur = nex;
    }
    ll tot = 0;
    rep(i, 0, n){
        tot += i ^ ans[i];
    }
    cout << tot << "\n";
    rep(i, 0, n){
        cout << ans[i] << " ";
    }
    cout << "\n";
}