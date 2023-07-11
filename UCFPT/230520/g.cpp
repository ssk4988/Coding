#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc; 
    rep(cn, 0, nc){
        vpi v;
        while(true){
            int a, b; cin >> a >> b;
            if(a == 0 && b == 0) break;
            v.push_back({b, a});
        }
        sort(all(v));
        int start = 0;
        int ans = 0;
        rep(i, 0, sz(v)){
            if(v[i].second >= start){
                ans++;
                start = v[i].first;
            }
        }
        cout << ans << "\n";
    }
}