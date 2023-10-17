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

vector<vl> pyramid;
ll target; 
int n;


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // takes in input from standard input
    string targetword; cin >> targetword;
    // one assumption I make is that the word fits into a 64-bit integer
    cin >> target;
    vector<string> rows;
    string line;
    while(cin >> line) {
        rows.push_back(line);
        cout << line << endl;
    }
    n = sz(rows);
    for(string row : rows) {
        istringstream input(row);
        string placeholder;
        vl numbers;
        while(getline(input, placeholder, ',')){
            numbers.pb(stoll(placeholder));
        }
    }
    
    return 0;
}
