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
    auto parity = [](ll n) -> int {
        return __builtin_popcountll(n) % 2;
    };
    auto even = [&]()-> ll {
        ll a, b; cin >> a >> b;
        return (parity(a) ? b : a);
    };
    auto domove = [](ll n) -> void {
        ll y = 1LL << __lg(n); n ^= y;
        cout << y << " " << n << endl;
    };
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        if(parity(n)){
            cout << "second" << endl;
            n = even();
        }
        else{
            cout << "first" << endl;
        }
        while(n != 0){
            domove(n);
            n = even();
        }
    }

    
    return 0;
}
