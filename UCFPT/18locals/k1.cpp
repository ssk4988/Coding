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
    ll ans = 0;
    ll lim = 1e15;
    ll i = 1;
    for(i = 1; ans < lim; i++){
        ll divs = 0;
        for(ll j = 1; j * j <= i && j <= 2; j += 1){
            if(i % j == 0){ 
                divs++;
                if(j * j < i) divs++;
            }
        }
        for(ll j = 3; j * j <= i; j += 2){
            if(i % j == 0){ 
                divs++;
                if(j * j < i) divs++;
            }
        }
        // if(i == 1) divs = 1;
        // if(i == 2) divs = 2;
        // cout << i << " has " << divs << " divs\n";
        ans += i * divs;
    }
    cout << (i - 1) << " " << ans << "\n";
}
