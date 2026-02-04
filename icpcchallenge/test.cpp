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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

auto gettime() {
    return chrono::steady_clock::now().time_since_epoch().count();
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    auto start = gettime();
    int x = 0;
    rep(i, 0, 500000) {
        x += rand() % 10;
    }
    cout << x << "\n";
    auto t1 = gettime();
    cout << (t1-start) << "\n";
    
    
    return 0;
}
