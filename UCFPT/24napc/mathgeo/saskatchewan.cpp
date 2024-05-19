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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    vll p;
    ll area = 0;
    {
        ll x, y;
        while(cin >> x >> y) {
            p.push_back({x, y});
        }
    }
    int n = sz(p);
    ll boundary = 0;
    rep(i, 0, n){
        area += p[i].f * p[(i+1)%n].s - p[i].s * p[(i+1)%n].f;
        boundary += __gcd(abs(p[i].f - p[(i+1)%n].f), abs(p[i].s - p[(i+1)%n].s));
        cout << boundary << "\n";
    }
    area = abs(area);
    ll interior = (area - boundary + 2) / 2 + boundary;
    cout << interior << "\n";
    
    return 0;
}
