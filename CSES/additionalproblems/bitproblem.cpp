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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int LIM = 1 << 20;
    vi a(LIM), v;
    int n; cin >> n;
    rep(i, 0, n){
        int k; cin >> k;
        a[k]++;
        v.pb(k);
    }
    vi subsum(a), supersum(a);
    rep(i, 0, 20){
        rep(j, 0, LIM){
            if(j & (1 << i)){
                subsum[j] += subsum[j ^ (1 << i)];
            }
            else{
                supersum[j] += supersum[j ^ (1 << i)];
            }
        }
    }
    for(int i : v){
        cout << subsum[i] << " " << supersum[i] << " ";
        int inverted = i;
        rep(j, 0, 20){
            inverted ^= 1 << j;
        }
        cout << (n - subsum[inverted]) << nL;
    }
    
    return 0;
}
