#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n, k; cin >> n >> k;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < k; i++){
            vl a1(a.size() - 1);
            for(int j = 0; j < a1.size(); j++) a1[j] = a[j] + a[j + 1];
            a = a1;
        }
        for(int i = 0; i < a.size(); i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
}
