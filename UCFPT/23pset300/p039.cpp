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

ll MOD = 1e9 + 7;
ll base = 3;
vl pows;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int a, b, len, n;
int ans = -1, target;
unordered_set<ll> hashes;
vl arr, pref;

void bt(int used, int pre, ll curhash){
    if(ans != -1) return;
    if(used == target){
        if(!hashes.count(curhash)) ans = target;
        return;
    }
    for(int i = pre + 1; i < len && target - used <= len - i; i++){
        ll newhash = mod(curhash - mod(arr[a + i] * pows[n + i]));
        newhash = mod(newhash + mod((3 - arr[a + i]) * pows[n + i]));
        bt(used + 1, i, newhash);
        if(ans != -1) return;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    pows.pb(1);
    rep(i, 0, 1e5){
        pows.pb(mod(base * pows.back()));
    }
    int q; 
    while(true){
        cin >> n >> q;
        if(n == 0 && q == 0) break;
        string str; cin >> str;
        arr = vl(n), pref = vl(n);
        rep(i, 0, n) arr[i] = str[i] - '0' + 1;
        rep(i, 0, n){
            pref[i] = mod(arr[i] * pows[i]);
            if(i > 0) pref[i] = mod(pref[i] + pref[i - 1]);
        }
        rep(i, 0, q){
            cin >> a >> b;
            a--,b--;
            ans = -1;
            len = b - a + 1;
            ll oldhash;
            hashes.clear();
            rep(j, 0, n - len + 1){
                ll h = pref[j + len - 1];
                if(j) h = mod(h - pref[j - 1]);
                h = mod(h * pows[n - j]);
                hashes.insert(h);
                if(j == a) oldhash = h;
            }
            ll checked = 0;
            ll choose = 1;
            for(target = 1; ans == -1 && target <= len; target++){
                choose *= len + 1 - target;
                choose /= target;
                if(checked + choose >= n + 1 - len){
                    ans = target;
                    break;
                }
                bt(0, -1, oldhash);
                checked += choose;
            }
            if(ans == -1){
                cout << "Impossible\n";
            }
            else{
                cout << ans << "\n";
            }
        }

    }
    
    return 0;
}
