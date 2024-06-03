#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vector<vii> pts = {{{0, 0},  {2, 0},{0, 1}, {2, 1}}, {{0, 2}, {1, 2}, {2, 2}, {3, 2}}};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    vi cnt(2);
    for(char c : str){
        int p = c - '0';
        // p = 1 - p;
        cout << pts[p][cnt[p]].f+1 << " " << pts[p][cnt[p]].s+1 << "\n";
        cnt[p]++;
        cnt[p]%=4;
    }
    
    return 0;
}
