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
    int nt;
    cin >> nt;
    string line;
    getline(cin, line);
    getline(cin, line);
    while (isspace(line.back()))
        line.pop_back();
    vector<string> tokens;
    {
        string token;
        for (char c : line)
        {
            if (isspace(c))
            {
                tokens.pb(token);
                token = "";
            }
            else
            {
                token.pb(c);
            }
        }
        if (sz(token))
            tokens.pb(token);
    }
    int n = sz(tokens);
    bool works = true;
    string ans;
    auto solve = [&](int start, auto &&solve) -> int {
        if(start == n){
            works = false;
            return -1;
        }
        if(tokens[start] == "int"){
            ans += "int";
            return start+1;
        }
        else if(tokens[start] == "pair"){
            ans += "pair<";
            int mid = solve(start+1, solve);
            if(!works) return -1;
            ans += ",";
            mid = solve(mid, solve);
            ans += ">";
            if(!works) return -1;
            return mid;
        }
        else{
            works = false;
            return -1;
        }
    };
    int last = solve(0, solve);
    if(last != n) works = false;
    if(works){
        cout << ans << "\n";
    }
    else cout << "Error occurred\n";

    return 0;
}
