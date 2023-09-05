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
    vvi grid(n, vi(m, 1));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, sz(str)){
            if(str[j] == '.') grid[i][j] = 0;
        }
    }
    vvi ways(n, vi(m));
    vi cols(m, n);
    int ans = 0;
    for(int i = n - 1; i >= 0; i--){
        rep(j, 0, m) if(grid[i][j]) cols[j] = i;
        stack<pi> st;
        st.push({i, -1});
        rep(j, 0, m){
            pi nex = {cols[j], j};
            while(st.top() > nex){
                auto [row, col] = st.top();
                st.pop();
                int pre = (sz(st) ? st.top().s : -1) + 1;
                ans = max(ans, (row - i) * (j - pre));
            }
            st.push(nex);
        }
        while(sz(st)){
            auto [row, col] = st.top();
            st.pop();
            int pre = (sz(st) ? st.top().s : -1) + 1;
            ans = max(ans, (row - i) * (m - pre));
        }
    }
    cout << ans << nL;
    
    return 0;
}
