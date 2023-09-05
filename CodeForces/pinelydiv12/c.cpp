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
        int n, k; cin >> n >> k;
        vi freq(n + 1);
        vi a(n), nex(n + 1);
        rep(i, 0, n){
            cin >> a[i];
            freq[a[i]]++;
        }
        vi a1(a);
        rep(j, 0, 2){
            int exc;
            rep(i, 0, n + 1){
                if(freq[i] == 0) exc = i;
            }
            rep(i, 0, n){
                nex[a[i]] = exc;
                freq[exc]++;
                freq[a[i]]--;
                swap(exc, a[i]);
            }
        }
        // rep(i, 0, n + 1){
        //     cout << i << " to " << nex[i] << nL;
        // }
        vvi cycles; vi visited(n + 1);
        rep(i, 0, n + 1){
            if(visited[i]) continue;
            cycles.pb({});
            int cur = i;
            while(!visited[cur]){
                visited[cur] = true;
                cycles.back().pb(cur);
                cur = nex[cur];
            }
        }
        vi after(n + 1);
        for(auto v : cycles){
            rep(i, 0, sz(v)){
                after[v[i]] = v[(i + k) % sz(v)];
            }
        }
        rep(i, 0, n){
            cout << after[a1[i]] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
