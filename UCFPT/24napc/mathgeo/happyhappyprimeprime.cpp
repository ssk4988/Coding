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
    cin.exceptions(cin.failbit);
    const int N = 10005;
    vi composite(N);
    vi state(N, -1);
    state[1] = 1;
    composite[0] = composite[1] = true;
    rep(i, 2, N){
        if(!composite[i]){
            for(int j = 2 * i; j < N; j += i) composite[j] = true;
        }
    }
    auto go = [&](int u, auto &&go)->bool {
        if(state[u] != -1) return state[u] == -2;
        state[u] = -2;
        int sum = 0;
        int u1 = u;
        while(u1){
            int d = u1 % 10;
            sum += d * d;
            u1 /= 10;
        }
        if(!go(sum, go)){
            state[u] = state[sum];
            return false;
        }
        return true;
    };

    int nc; cin >> nc;
    rep(cn, 0, nc){
        int c, x; cin >> c >> x;
        go(x, go);
        cout << c << " " << x << " " << (!composite[x] && state[x] == 1 ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
