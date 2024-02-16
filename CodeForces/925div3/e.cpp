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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vi a(n);
        m++;
        int lensum = 0;
        multiset<int> pq;
        rep(i, 0, n){
            int v; cin >> v;
            lensum += sz(to_string(v));
            while(v % 10 == 0){
                a[i]++;
                v /= 10;
            }
            pq.insert(a[i]);
        }
        int rem = 0;
        rep(i, 0, n){
            auto it = prev(pq.end());
            rem += *it;
            pq.erase(it);
            pq.insert(0);
            if(i + 1 < n){
                it = prev(pq.end());
                pq.erase(it);
                pq.insert(0);
            }
        }
        lensum -= rem;
        cout << (lensum >= m ? "Sasha" : "Anna") << nL;
    }
    
    return 0;
}