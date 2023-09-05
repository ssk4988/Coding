#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    map<string, ll> freq;
    rep(i, 0, n){
        string str; cin >> str;
        freq[str]++;
    }
    vector<vl> fs(26);
    for(auto [key, val] : freq){
        fs[key[0] - 'A'].pb(val);
    }
    ll ans = 0;
    rep(i, 0, 26){
        ll sum = 0;
        for(ll j : fs[i]) sum += j;
        for(ll j : fs[i]) ans += (sum - j) * j;
    }
    cout << ans << "\n";
}
