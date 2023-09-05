#include <bits/stdc++.h>
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
    int n;ll k; cin >> n >> k;
    for(int i = n; i > 0; i--){
        if(k > i - 1){
            cout << i << " ";
            k -= i - 1;
        }
        else{
            vi rest(i);
            rest[i - 1 - k] = i;
            int v = 1;
            rep(j, 0, i){
                if(rest[j] == 0) rest[j] = v++;
                cout << rest[j] << " ";
            }
            break;
        }
    }
    cout << nL;
    
    return 0;
}
