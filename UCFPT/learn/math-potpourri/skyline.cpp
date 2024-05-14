#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll MOD = 1000000;
const int MAX_N = 1005;
ll cat[MAX_N];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cat[0] = 1;
    rep(i, 1, MAX_N){
        rep(j, 0, i){
            (cat[i] += cat[j] * cat[i - 1 - j] % MOD) %= MOD;
        }
    }
    int n; 
    while(true){
        cin >> n;
        if(n==0) break;
        cout << cat[n] << "\n";
    }
    return 0;
}
