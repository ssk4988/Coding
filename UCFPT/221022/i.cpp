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

#define maxM 10
#define maxL 25


struct state;
struct Node
{
    // (nmatches is optional)
    int back, next[26], start = -1, end = -1, nmatches = 0;
    ll dp[maxL + 1][1 << maxM];
    vector<state> prev[maxL + 1][1 << maxM];

    int bit = 0;
    Node(int v)
    {
        memset(next, v, sizeof(next));
        memset(dp, 0, sizeof dp);
    }
};
struct state
{
    Node *p;
    int len;
    int bit;
    char c;
};

struct AhoCorasick
{
    enum
    {
        alpha = 26,
        first = 'a'
    }; // change this!

    vector<Node> N;
    vi backp;
    void insert(string &s, int j)
    {
        assert(!s.empty());
        int n = 0;
        for (char c : s)
        {
            int &m = N[n].next[c - first];
            if (m == -1)
            {
                n = m = sz(N);
                N.emplace_back(-1);
            }
            else
                n = m;
        }
        if (N[n].end == -1)
            N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
        N[n].bit |= 1 << j;
    }
    AhoCorasick(vector<string> &pat) : N(1, -1)
    {
        rep(i, 0, sz(pat)) insert(pat[i], i);
        N[0].back = sz(N);
        N.emplace_back(0);

        queue<int> q;
        for (q.push(0); !q.empty(); q.pop())
        {
            int n = q.front(), prev = N[n].back;
            rep(i, 0, alpha)
            {
                int &ed = N[n].next[i], y = N[prev].next[i];
                if (ed == -1)
                    ed = y;
                else
                {
                    N[ed].back = y;
                    N[ed].bit |= N[y].bit;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    q.push(ed);
                }
            }
        }
    }
    vi find(string word)
    {
        int n = 0;
        vi res; // ll count = 0;
        for (char c : word)
        {
            n = N[n].next[c - first];
            res.push_back(N[n].end);
            // count += N[n].nmatches;
        }
        return res;
    }
    vector<vi> findAll(vector<string> &pat, string word)
    {
        vi r = find(word);
        vector<vi> res(sz(word));
        rep(i, 0, sz(word))
        {
            int ind = r[i];
            while (ind != -1)
            {
                res[i - sz(pat[ind]) + 1].push_back(ind);
                ind = backp[ind];
            }
        }
        return res;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    // test m == 0
    int nc = 1;
    while ((cin >> n >> m) && !(n == 0 && m == 0))
    {
        vector<string> words;
        rep(i, 0, m)
        {
            string k;
            cin >> k;
            words.pb(k);
        }
        AhoCorasick ac(words);
        ac.N[0].dp[0][0] = 1;
        int maxbit = 1 << m;
        rep(i, 0, n)
        {
            rep(j, 0, ac.N.size())
            {
                rep(k, 0, maxbit)
                {
                    if (ac.N[j].dp[i][k])
                    {
                        rep(l, 0, 26)
                        {
                            ac.N[ac.N[j].next[l]].dp[i + 1][k | ac.N[ac.N[j].next[l]].bit] += ac.N[j].dp[i][k];
                            if (ac.N[ac.N[j].next[l]].dp[i + 1][k | ac.N[ac.N[j].next[l]].bit] <= 42)
                            {
                                ac.N[ac.N[j].next[l]].prev[i + 1][k | ac.N[ac.N[j].next[l]].bit].pb({&ac.N[j], i, k, (char)('a' + l)});
                            }
                            // if(ac.N[ac.N[j].next[l]].prev[i + 1][k | ac.N[ac.N[j].next[l]].bit].size() > 42){
                            //     cout << ac.N[ac.N[j].next[l]].prev[i + 1][k | ac.N[ac.N[j].next[l]].bit].size() << nL;
                            // }
                        }
                    }
                }
            }
        }
        ll ans = 0;
        rep(i, 0, ac.N.size())
        {
            ans += ac.N[i].dp[n][maxbit - 1];
        }

        cout << "Case " << nc << ": " << ans << " suspects" << nL;
        if (ans <= 42)
        {
            vector<string> sols;
            queue<pair<state, string>> q;
            rep(i, 0, ac.N.size())
            {
                if (ac.N[i].dp[n][maxbit - 1])
                    q.push({{&ac.N[i], n, maxbit - 1, ' '}, ""});
            }
            while (!q.empty())
            {
                pair<state, string> p = q.front();
                if (p.s.length() < n)
                {
                    for (auto &k : (*(p.f.p)).prev[p.f.len][p.f.bit])
                    {
                        q.push({k, p.s + k.c});
                    }
                }
                else
                {
                    reverse(all(p.s));
                    sols.pb(p.s);
                }
                q.pop();
            }
            sort(all(sols));
            for(string k : sols){
                cout << k << nL;
            }
        }

        nc++;
    }

    return 0;
}