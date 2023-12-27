#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

using vl = vector<ll>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(_, 0, nc){
        int cn, n; cin >> cn >> n;
        vi a(n);
        vi lef(n), rig(n);
        queue<int> q;
        rep(i, 0, n){
            cin >> a[i];
            lef[i] = (i + n - 1) % n;
            rig[i] = (i + 1) % n;
            if(a[i] == 1){
                q.push(i);
            }
        }
        bool works = true;
        vvi ans;
        while(!q.empty()){
            int k = q.front(); q.pop();
            if(a[k] != 1){
                works = false;
                break;
            }
            a[lef[k]]--;
            a[rig[k]]--;
            a[k]--;
            if(a[lef[k]] == 0 && a[rig[k]] == 0){
                ans.push_back({lef[k], rig[k], k});
                // should be last thing
                break;
            }
            if(a[lef[k]] <= a[k] || a[rig[k]] <= a[k]){
                works = false;
                break;
            }
            ans.push_back({lef[k], rig[k], k});
            rig[lef[k]] = rig[k];
            lef[rig[k]] = lef[k];
            if(a[lef[k]] == 1) q.push(lef[k]);
            if(a[rig[k]] == 1) q.push(rig[k]);
        }
        if(*max_element(all(a)) != 0){
            works = false;
        }
        if(!works){
            cout << cn << " N\n";
            continue;
        }
        cout << cn << " Y\n";
        for(auto &v : ans) sort(all(v));
        sort(all(ans));
        for(auto v : ans){
            for(int i : v) cout << (i + 1) << " ";
            cout << "\n";
        }
    }
    return 0;
}
