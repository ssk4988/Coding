#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using ld = long double;

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, m;
    auto sum1 = [](ll i)->ll{
        return i * (i + 1) / 2;
    };
    auto sum2 = [](ll i)->ll{
        return i * (2 * i + 1) * (i + 1) / 6;
    };
    auto sum3 = [](ll i)->ll{
        return i * i * (i + 1) * (i + 1) / 4;
    };
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        ll maxi = min(n, m) / 2;
        ll ans = 8 * sum3(maxi) + (n * m) * (maxi + 1) + ((-2)*(n + m) + 2 * n * m)*sum1(maxi) + (4 + (-4)*(n + m))*sum2(maxi);
        cout << ans << "\n";
    }
}