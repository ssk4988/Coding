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
 
bool cmp(pi a, pi b){
    return a.f >= b.f;
    // if(a.f >= b.f) return true;
    // return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vvi grid(n, vi(m, 1));
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        rep(j, 0, sz(str))
        {
            if (str[j] == '.')
                grid[i][j] = 0;
        }
    }
    vvi ways(n + 1, vi(m + 1));
    vi cols(m, n); // highest in each col we have seen (lowest row index)
    for (int i = n - 1; i >= 0; i--)
    {
        rep(j, 0, m) if (grid[i][j]) cols[j] = i;
        vector<pi> st;
        st.pb({i, -1});
        // cout << "testing row " << i << endl;
        rep(j, 0, m)
        {
            pi nex = {cols[j], j};
            while (sz(st) && cmp(st.back(), nex))
            {
                // auto [row, col] = st.back();
                st.pop_back();
                // int pre = (sz(st) ? st.back().s : -1) + 1;
                // if (row - i > 0 && j - pre > 0)
                // {
                //     ways[row - i][j - pre]++;
                // }
            }
            st.pb(nex);
            rep(k, 0, sz(st)){
                auto [row, col] = st[k];
                int pre = k ? st[k - 1].s : -1;
                ways[row - i][j - pre]++;
                if(k){
                    ways[st[k - 1].f - i][j - pre]--;
                }
            }
        }
    }
    for(int i = n; i > 0; i--){
        for(int j = m; j > 0; j--){
            if(i + 1 <= n) ways[i][j] += ways[i + 1][j];
            if(j + 1 <= m) ways[i][j] += ways[i][j + 1];
            if(i + 1 <= n && j + 1 <= m) ways[i][j] -= ways[i + 1][j + 1];
        }
    }
    rep(i, 1, n + 1){
        rep(j, 1, m + 1){
            cout << ways[i][j] << " ";
        }
        cout << nL;
    }
 
    return 0;
}
