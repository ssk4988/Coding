#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;
const bool DEBUG = false;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    unordered_set<int> births;
    rep(i, 0, n){
        cin >> a[i];
        if(a[i] != -1) births.insert(i - a[i]);
    }
    for(int b : births){
        rep(i, 0, k){
            if(b + i < n) a[b + i] = i;
        }
    }
    int pre = n;
    vi nex(n, -1);
    for(int i = n - 1; i >= 0; i--){
        if(a[i] == -1) nex[i] = pre;
        else pre = i;
    }
    if(DEBUG){
        rep(i, 0, n) cout << a[i] << " " ;
        cout << "\n";
        rep(i, 0, n) cout << nex[i] << " ";
        cout << "\n";
    }
    int w = k;
    int bs = sz(births);
    for(int i = 0; i < n; i++){
        if(a[i] != -1) continue;
        if(nex[i] == n){
            // no known knowledge to the end of time
            bs += (nex[i] - i + w - 1) / w;
        }
        else{
            bs += (nex[i] - i) / w;
        }
        i = nex[i];
    }
    cout << bs << "\n";
}
