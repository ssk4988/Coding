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

const int bits = 29; // should be 29 actually



const int N = 1200300, LOGN = 30, V = N * LOGN;

int sum[V];
int c[V][2];
int used = 1;
int alloc(){
    return used++;
}

void push(int n, int k){
    if(c[n][k] != 0) return;
    // cout << "created node for bit "<<k << " " << c[n][k] << " now is ";
    c[n][k] = alloc();
}

void add(int n, int b, int dep=bits){
    sum[n]++;
    if(dep == -1){
        return;
    }
    push(n, (b >> dep) & 1);
    add(c[n][(b >> dep) & 1], b, dep-1);
}

int xorgeq(int n, int a, int k, int dep=bits){
    if(dep == -1) return sum[n];
    int ans = 0;
    int ab = (a >> dep) & 1, kb = (k >> dep) & 1;
    if(ab && kb){
        push(n, 0);
        ans += xorgeq(c[n][0], a, k, dep-1);
    }
    else if(ab && !kb){
        push(n, 1);
        ans += sum[c[n][0]];
        ans += xorgeq(c[n][1], a, k, dep-1);
    }
    else if(!ab && kb){
        push(n, 1);
        ans += xorgeq(c[n][1], a, k, dep-1);
    }
    else if(!ab && !kb){
        push(n, 0);
        ans += xorgeq(c[n][0], a, k, dep-1);
        ans += sum[c[n][1]];
    }
    return ans;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    alloc();
    alloc();
    int root = alloc();
    // Trie* root = new Trie();
    // cout << "start" << root << endl;
    add(root, 0);
    // cout << "added" << endl;
    // cout << xorgeq(0, 0) << "\n";
    // cout << xorgeq(0, 0) << "\n";
    ll ans = 0;
    rep(i, 0, n){
        cin >> a[i];
        if(i) a[i] ^= a[i-1];
        int val = xorgeq(root, a[i], k);
        // cout << val << " " << sum << " " << sz(tries) << "\n";
        ans += val;
        add(root, a[i]);
    }
    cout << ans << "\n";
    
    return 0;
}