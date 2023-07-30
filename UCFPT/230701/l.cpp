#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    freopen("mahdi.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cout << "Case " << (cn + 1) << ":\n";
        vector<vi> occ(26);
        char c; int len, mult, add; cin >> c >> len >> mult >> add;
        int cur = c - 'a';
        occ[cur].push_back(0);
        rep(i, 1, len){
            cur = (cur * mult + ll(i) * add) % 26;
            occ[cur].push_back(i);
        }
        int n; cin >> n;
        rep(t, 0, n){
            cin >> c >> len >> mult >> add;
            bool works = true;
            int cur = c - 'a';
            int idx;
            if(occ[cur].size() == 0){
                works = false;
            }
            else idx = *occ[cur].begin();
            rep(i, 1, len){
                if(!works) break;
                cur = (cur * mult + ll(i) * add) % 26;
                // auto it = occ[cur].upper_bound(idx);
                int lo = 0, hi = sz(occ[cur]);
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(occ[cur][mid] > idx) hi = mid;
                    else lo = mid + 1;
                }
                if(lo == sz(occ[cur])){
                    works = false;
                }
                else idx = occ[cur][lo];
            }
            if(works) cout << "BRAVO\n";
            else cout << "REPEAT\n";
        }
    }
}
