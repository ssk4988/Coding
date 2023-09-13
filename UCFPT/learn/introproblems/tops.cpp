#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using vi = vector<int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; cin >> n;
        int mx = INT_MIN, mn = INT_MAX;
        vi a(n);
        for(int i = 0; i < n; i++){
            string str; cin >> str >> a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }
        sort(a.begin(), a.end());
        cout << "Case #" << (cn + 1) << ": " << mx << " " << mn << " ";
        if(n % 2 == 1){
            cout << a[n / 2] << "\n";
        }
        else{
            int sum = a[n/2] + a[n/2-1];
            cout << sum/2 << ((sum % 2 + 2) % 2 == 1 ? ".5" : "") << "\n";
        }
    }
}
