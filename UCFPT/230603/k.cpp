#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<char> v = {'c', 'f', 'i', 'l', 'o', 's', 'v', 'z'};
    vi v1 = {2, 3, 4, 5, 6, 7, 8, 9};
    int n, q; cin >> n >> q;
    unordered_map<ll, int> freq;
    rep(i, 0, n){
        string str; cin >> str;
        ll val = 0;
        rep(j, 0, sz(str)){
            rep(k, 0, sz(v)){
                if(str[j] <= v[k]){
                    val *= 10;
                    val += v1[k];
                    break;
                }
            }
        }
        freq[val]++;
    }
    rep(i, 0, q){
        ll val; cin >> val;
        cout << freq[val] << "\n";
    }
    return 0;
}
