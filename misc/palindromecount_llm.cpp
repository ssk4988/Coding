#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pd> vpd;

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

bool check(string& x) {
    string temp = x;
    reverse(all(temp));
    return x == temp;
}

int cnt(string& x) {
    set<string> have;
    for(int i = 0; i < x.size(); i++) {
        for(int j = i; j < x.size(); j++) {
            string curr = x.substr(i, j - i + 1);
            if(check(curr)) have.insert(curr);
        }
    }

    return have.size() == x.size() ? 1 : 0;
}


ll ans = 0;
void rec(string& curr, int index, int stop, int lim) {
    if(index == stop) {
        if(cnt(curr) == 1) {
            ll have = stop;
            ll here = 1;
            for(int i = 0; i < lim; i++) {
                here *= have;
                have--; 
            }
            ans += here;
        }
        return;
    }
    for(int i = 0; i < min(stop, lim + 1); i++) {
        char j = (char) ('a' + i);
        curr += j;
        rec(curr, index + 1, stop, max(lim, i + 1));
        curr.pop_back();
    }
}

void solve() {
    for(int i = 1; i <= 14; i++) {
        string init;
        ans = 0;
        rec(init, 0, i, 0);

        long double res = ans;
        ll div = 1;
        for(int j = 0; j < i; j++) div *= i;
        res /= div;
        cout << i << " " << ans << ' ';
        cout << fixed << setprecision(10) << res << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc = 1;
    // cin >> tc;

    for(int tt = 1; tt <= tc; tt++) {
        solve();
    }

    return 0;
}
