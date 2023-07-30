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

/**
 * Author: Jacob Steinebronn
 * Date: 09/20/2022
 * Description: Generates an eertree on str. $cur$ is accurate at the end of the main loop before the final assignment to $t$.
 * Time: $O(|S|)$
 * Status: Works but not stress-tested
 */
int main()
{
    string str;
    vi slink = {0, 0}, len = {-1, 0};
    vvi down(2, vi(26, -1));
    int cur = 0, t = 0;
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        int ci = c - 'a';
        while (t <= 0 || str[t - 1] != c)
            t = i - len[cur = slink[cur]];
        if (down[cur][ci] == -1)
        {
            down[cur][ci] = slink.size();
            down.emplace_back(26, -1);
            len.pb(len[cur] + 2);
            if (len.back() > 1)
            {
                do
                    t = i - len[cur = slink[cur]];
                while (t <= 0 || str[t - 1] != c);
                slink.pb(down[cur][ci]);
            }
            else
                slink.pb(1);
            cur = slink.size() - 1;
        }
        else
            cur = down[cur][ci];
        t = i - len[cur] + 1;
    }
}
