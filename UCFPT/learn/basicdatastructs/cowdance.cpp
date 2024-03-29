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
    int n, t; cin >> n >> t;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    auto test = [&](int k) -> bool {
        int time = 0;
        priority_queue<int, vi, greater<int>> pq;
        rep(i, 0, k){
            pq.push(a[i]);
        }
        int pnt = k;
        while(pq.size()){
            int b = pq.top(); pq.pop();
            time = b;
            if(pnt < n){
                pq.push(time + a[pnt]);
                pnt++;
            }
        }
        return time <= t;
    };
    int x = 0;
    for(int dif = 1 << 20; dif; dif >>= 1){
        if(x + dif <= n && !test(x + dif)){
            x += dif;
        }
    }
    x++;
    cout << x << "\n";

    
    return 0;
}
