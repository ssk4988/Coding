#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int d; cin >> d;
        vector<ll> ds(d);
        for(int d1 = 0; d1 < d; d1++){
            cin >> ds[d1];
        }
        ll lo = 0, hi = 1005;
        pair<ll, ll> best = {LLONG_MAX, 0};
        for(ll mid = 0; mid < 1005; mid++){
            ll maxleft = 0, minleft = 0;
            ll left = 0;
            for(ll v : ds){
                left += mid - v;
                maxleft = max(left, maxleft);
                minleft = min(left, minleft);
            }
            if(minleft >= 0){
                best = min(best, {mid, maxleft});
            }
        }
        cout << best.first << " " << best.second << "\n";
    }
}
