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
    string str; cin >> str;
    int n = sz(str);
    int v = stoi(str, NULL, 2);
    queue<int> q;
    q.push((1 << n) - 1);
    int ans = INT_MAX;
    rep(i, 0, 30){
        set<int> q1;
        while(!q.empty()){
            int v1 = q.front();q.pop();
            if(v1 == v){
                ans = i;
                break;
            }
            // q1.push(v1);
            int mask = 0;
            int upb = min(n, i + 1);
            rep(j, 0, upb){
                mask |= 1 << j;
            }
            mask <<= n - upb;
            rep(j, 0, n + 1){
                q1.insert(v1 ^ mask);
                mask >>= 1;
            }
        }
        if(ans != INT_MAX){
            break;
        }
        for(int v1 : q1){
            q.push(v1);
        }
        // q = q1;
    }
    assert(ans != INT_MAX);
    cout << ans << nL;
    return 0;
}
