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

vector<vvi> dp;
string name[3];
int lens[3];
string ans;

vvi nextstates(vi &state)
{
    vvi ans;
    bool skip[3] = {};
    rep(i, 0, 3)
    {
        if (skip[i] || state[i] == name[i].length())
            continue;
        vi nstate(state);
        for (int j = 2; j >= i; j--)
        {
            if (state[j] < name[j].length() && name[i][state[i]] == name[j][state[j]])
            {
                nstate[j]++;
                skip[j] = true;
            }
        }
        ans.pb(nstate);
    }
    return ans;
}

void dfs(vector<char> &cur, vi &state)
{
    if (dp[state[0]][state[1]][state[2]] < 0)
        return;
    if (state[0] == lens[0] && state[1] == lens[1] && state[2] == lens[2])
    {
        string s1 = string(cur.begin(), cur.end());
        if (s1.compare(ans) < 0)
        {
            ans = s1;
        }
        return;
    }
    dp[state[0]][state[1]][state[2]] = -1;
    set<char> changes;
    rep(i, 0, 3)
    {
        if (state[i] < lens[i])
        {
            changes.insert(name[i][state[i]]);
        }
    }
    for (char c : changes)
    {
        vi nstate(state);
        rep(i, 0, 3)
        {
            if (state[i] < lens[i] && name[i][state[i]] == c)
                nstate[i]++;
        }
        cur.pb(c);
        if (dp[nstate[0]][nstate[1]][nstate[2]] == cur.size())
        {
            dfs(cur, nstate);
        }
        cur.pop_back();
    }
    // for (vi &nstate : nextstates(state))
    // {
    //     rep(i, 0, 3)
    //     {
    //         if (nstate[i] != state[i])
    //         {
    //             cur.pb(name[i][state[i]]);
    //             if (dp[nstate[0]][nstate[1]][nstate[2]] == cur.size())
    //             {
    //                 dfs(cur, nstate);
    //             }
    //             cur.pop_back();
    //             break;
    //         }
    //     }
    // }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    auto start = std::chrono::high_resolution_clock::now();
    rep(cn, 0, nc)
    {
        ans = "";

        rep(i, 0, 3)
        {
            cin >> name[i];
            lens[i] = name[i].length();
        }
        dp = vector<vvi>(name[0].length() + 1, vvi(name[1].length() + 1, vi(name[2].length() + 1, 400)));
        dp[0][0][0] = 0;
        vi state(3);
        rep(i, 0, lens[0] + 1)
        {
            state[0] = i;
            rep(j, 0, lens[1] + 1)
            {
                state[1] = j;
                rep(k, 0, lens[2] + 1)
                {
                    state[2] = k;
                    for (vi &nstate : nextstates(state))
                    {
                        dp[nstate[0]][nstate[1]][nstate[2]] = min(dp[nstate[0]][nstate[1]][nstate[2]], dp[i][j][k] + 1);
                    }
                }
            }
        }
        int anslen = dp[name[0].length()][name[1].length()][name[2].length()];
        // cout << anslen << nL;
        rep(i, 0, anslen)
        {
            ans += 'z';
        }
        vector<char> cur;
        fill(state.begin(), state.end(), 0);
        dfs(cur, state);
        cout << ans << nL;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1e6 << nL;
    return 0;
}