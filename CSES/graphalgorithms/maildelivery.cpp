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
    int n, m; cin >> n >> m;
    vector<unordered_set<int>> adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].insert(b);adj[b].insert(a);
    }
    bool works = true;
    rep(i, 0, n){
        if(sz(adj[i]) % 2 == 1) works = false;
    }
    if(!works){
        cout << "IMPOSSIBLE\n" << nL;
        return 0;
    }
    stack<int> st;
    vi ans;
    st.push(0);
    while(st.size()){
        if(sz(adj[st.top()]) == 0){
            ans.pb(st.top());
            st.pop();
        }
        else{
            for(int i : adj[st.top()]){
                adj[st.top()].erase(i);
                adj[i].erase(st.top());
                st.push(i);
                break;
            }
        }
    }
    if(sz(ans) != m + 1){
        cout << "IMPOSSIBLE\n";return 0;
    }
    rep(i, 0, sz(ans)){
        cout << (1 + ans[i]) << " ";
    }
    cout << nL;
    
    return 0;
}
