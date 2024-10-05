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

/*

*/

int getrank(string &s)
{
    int bcnt = 0;
    int ans = 0;
    for (char c : s)
    {
        if (c == 'A')
            ans += bcnt;
        else if (c == 'B')
            bcnt++;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    string start;
    cin >> start;
    if (n == 3)
    {
        vector<string> bad = {
            "..ABAB",
            "..BABA",
            "A..BBA",
            "AB..AB",
            "ABAB..",
            "ABB..A",
            "B..AAB",
            "BA..BA",
            "BAA..B",
            "BABA.."};
        bool has_bad = false;
        for (auto s : bad)
        {
            if (start == s)
            {
                has_bad = true;
            }
        }
        if (has_bad)
        {
            cout << "-1\n";
            return 0;
        }
    }
    string cur(start);
    vector<string> res;
    while (getrank(cur) != 0)
    {
        int r = getrank(cur);
        // cout << "improve " << cur << " " << r << endl;
        map<string, string> reach; // cur to prev
        queue<string> q;
        q.emplace(cur);
        reach[cur] = "";
        pair<int, string> best{1e9, ""};
        while (sz(q))
        {
            auto s = q.front();
            q.pop();

            vi places;
            rep(i, 0, sz(s) - 1)
            {
                if (s[i] != '.' && s[i + 1] != '.')
                    places.push_back(i);
            }

            rep(i, 0, sz(s) - 1)
            {
                if (s[i] != '.' || s[i + 1] != '.')
                    continue;
                for (int p : places)
                {
                    string t(s);
                    swap(t[i], t[p]);
                    swap(t[i + 1], t[p + 1]);
                    if (reach.count(t))
                        continue;
                    reach[t] = s;
                    int r1 = getrank(t);
                    if (r1 < r)
                    {
                        best = min(best, {r1, t});
                        goto fnd;
                    }
                    q.emplace(t);
                }
            }
        }
        fnd:
        string use = best.second;
        if (!sz(use))
        {
            cout << "-1\n";
            exit(0);
        }
        assert(sz(use));
        vector<string> mv;
        while (use != cur)
        {
            mv.pb(use);
            use = reach[use];
        }
        cur = mv.front();
        while (sz(mv))
        {
            res.pb(mv.back());
            mv.pop_back();
        }
    }
    cout << sz(res) << "\n";
    for (auto s : res)
        cout << s << "\n";

    return 0;
}
