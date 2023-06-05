#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n;int q; cin >> n >> q;
    vvl corners = {{1, n}, {n * n - n + 1, n * n}};
    rep(i, 0, q){
        char ch; cin >> ch;
        if(ch == 'q'){
            ll r, c; cin >> r >> c;
            r--, c--;
            if(n == 1){
                cout << 1 << "\n";
                continue;
            }
            ll base = corners[0][0];
            ll rdif = (corners[1][0] - corners[0][0]) / (n - 1);
            ll cdif = (corners[0][1] - corners[0][0]) / (n - 1);
            base += rdif * r + cdif * c;
            cout << base << "\n";
        }
        else{
            char t; cin >> t;
            if(t == 'a'){
                swap(corners[0][1], corners[1][0]);
            }
            if(t == 'b'){
                swap(corners[0][0], corners[0][1]);
                swap(corners[1][0], corners[1][1]);
            }
            if(t == 'c'){
                swap(corners[0][0], corners[1][1]);
            }
            if(t == 'd'){
                swap(corners[0][0], corners[1][0]);
                swap(corners[0][1], corners[1][1]);
            }
        }
    }
    return 0;
}
