#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; cin >> n;
        multiset<int> def;
        vector<int> att(n);
        for(int i = 0; i < n; i++){
            cin >> att[i];
        }
        for(int i = 0; i < n; i++){
            int v; cin >> v;
            def.insert(v);
        }
        int ans = 0;
        sort(att.begin(), att.end());
        for(int i : att){
            if(def.lower_bound(i) != def.end()){
                def.erase(def.lower_bound(i));
                ans++;
            }
        }
        cout << ans << "\n";
    }
}
