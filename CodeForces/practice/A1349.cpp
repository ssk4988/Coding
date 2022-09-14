#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int freq[200005];

ll gcd(ll a, ll b){
    if(a == 0)return b;
    return gcd(b%a, a);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    memset(freq, 0, sizeof freq);
    rep(i, 0, n){
        int a; cin >> a;
        for(int j = 1; j * j <= a; j++){
            if(a % j == 0){
                freq[j]++;
                if(j * j != a){
                    freq[a/j]++;
                }
            }
        }
    }
    ll ans = 1;
    rep(i, 1, 200005){
        if(freq[i]>n-2){
            ans = ans / gcd(ans, i) * i;
        }
    }
    cout << ans << nL;
    
    return 0;
}