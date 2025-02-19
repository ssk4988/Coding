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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    ll zero = 0;
    priority_queue<int, vi, greater<>> d;
    rep(i, 0, n) {
        int p; cin >> p;
        if(sz(d) && d.top() < p) {
            zero += p - d.top();
            d.pop();
            d.push(p);
        }
        d.push(p);
    }
    cout << zero << "\n";
    
    return 0;
}
