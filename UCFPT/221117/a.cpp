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
    ll n;
    while(cin >> n){
        int cnt = 0;
        ll n1 = 1;
        while(n1 < n){
            if(cnt % 2 == 0){
                n1 *= 9;
            }
            else{
                n1 *= 2;
            }
            cnt++;
        }
        if(cnt % 2 == 1) cout << "Stan wins." << endl;
        else cout << "Ollie wins." << endl;
    }
    
    return 0;
}