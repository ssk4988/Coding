#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0;cn < nc; cn++){
        int n; cin >> n;
        vector<pair<vector<int>, string>> v(n);
        for(int i = 0; i < n; i++){
            cin >> v[i].second;
            v[i].first.resize(26);
            for(int j = 0; j < v[i].second.size(); j++){
                v[i].first[v[i].second[j] - 'A']++;
            }
        }
        sort(v.rbegin(), v.rend());
        cout << "Class #" << (cn + 1) << " ordering\n";
        for(auto [v1, str] : v){
            cout << str << "\n";
        }
        cout << "\n";
    }
}
