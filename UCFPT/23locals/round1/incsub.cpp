#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int best = 0, cur = 0, pre = -1;
    for(int i = 0; i < n; i++){
        int a; cin >> a;
        if(a > pre){
            cur++;
        }
        else cur = 1;
        pre = a;
        best = max(best, cur);
    }
    cout << best << "\n";
}
