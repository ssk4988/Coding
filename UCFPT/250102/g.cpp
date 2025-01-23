#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll a, b; cin >> a >> b;
        vector<set<ll>> seen(a+1);
        queue<array<ll, 3>> q;
        {
            ll g = gcd(a, b);
            a /= g, b /= g;
            q.push({0, a, b});
            seen[a].insert(b);
        }
        while(sz(q)){
            auto [d, x, y] = q.front(); q.pop();
            if(x == 0 && y == 0){
                cout << d << "\n";
                break;
            }
            if(x) {
                ll g = gcd(x-1, y);
                if(g == 0) g = 1;
                ll x1 = (x-1)/g, y1 = y/g;
                if(!seen[x1].count(y1)){
                    seen[x1].insert(y1);
                    q.push({d+1, x1, y1});
                }
            }
            if(y) {
                ll g = gcd(x, y-1);
                if(g == 0) g = 1;
                ll x1 = x/g, y1 = (y-1)/g;
                if(!seen[x1].count(y1)){
                    seen[x1].insert(y1);
                    q.push({d+1, x1, y1});
                }
            }
        }
    }
}
