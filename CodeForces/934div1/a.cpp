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
        int n; cin >> n;
        n++;
        vi freq(n);
        rep(i, 0, n-1){
            int v; cin >> v; freq[v]++;
        }
        auto test = [&](int t) -> bool {
            priority_queue<pi, vpi, greater<pi>> pq;
            rep(i, 0, min(t, n)){
                if(freq[i]) pq.push({freq[i], i});
            }
            set<int> has;
            int turn = 0;
            while(sz(pq)){
                auto [f, v] = pq.top(); pq.pop();
                if(turn == 0){
                    has.insert(v);
                }
                else{
                    f--;
                    if(f) pq.push({f, v});
                }
                turn = 1 - turn;
            }
            int mex = 0;
            for(int i : has) if(mex == i) mex++;
            return mex >= t;
        };
        int best = -1;
        for(int dif = 1 << 20; dif; dif /= 2){
            if(test(best + dif)) best += dif;
        }
        cout << best << "\n";
    }
    
    return 0;
}
