#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; ll x; cin >> n >> x;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        bool easy = false;
        rep(i, 0, n){
            if(a[i] >= x){
                cout << 1 << "\n";
                easy = true;
            }
        }
        if(easy) continue;
        if(x <= 0 && !easy){
            cout << "-1\n";
            continue;
        }
        set<ll> st;
        unordered_map<ll, int> midx;
        // {prefsum, idx}
        ll prefsum = 0;
        int ans = n + 1;
        rep(i, 0, n){
            prefsum += a[i];
            if(st.size()){
                auto it = st.upper_bound(prefsum - x);
                if(it != st.begin()){
                    it = prev(it);
                    ans = min(ans, i - midx[*it]);
                }
            }
            while(st.size()){
                auto it = st.lower_bound(prefsum);
                if(it != st.end()){
                    st.erase(*it);
                    midx.erase(*it);
                }
                else{
                    break;
                }
            }
            midx[prefsum] = i;
            st.insert(prefsum);
        }
        if(ans == n + 1) ans = -1;
        cout << ans << "\n";
    }
}