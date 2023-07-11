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
    ll k; int h, q; cin >> k >> h >> q;
    bool cycle = true;
    set<ll> lefts, rights;
    rep(i, 0, q){
        int t; ll a, b; cin >> t >> a >> b;
        if(b < a) swap(a, b);
        if(t == 1){
            ll ans = LLONG_MAX;
            auto it = lefts.lower_bound(a);
            if(it != lefts.end() && *it < b){}
            else ans = min(ans, b - a);
            if(cycle){
                it = lefts.lower_bound(b);
                if(it == lefts.end()){
                    it = rights.upper_bound(a);
                    if(it != rights.begin()){
                        it = prev(it);

                    }
                    else{
                        ans = min(ans, a - 0 + (k - 1 - b) + 1);
                    }
                }
            }
            if(ans == LLONG_MAX) ans = -1;
            cout << ans << "\n";
        }
        else if(t == 2){
            if(a == 0 && b == k - 1) cycle = false;
            else{
                lefts.insert(a);
                rights.insert(b);
            }
        }
        else{
            if(a == 0 && b == k - 1) cycle = true;
            else{
                lefts.erase(a);
                rights.erase(b);
            }
        }
    }
}