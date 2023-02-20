#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef long long ll;
typedef vector<ll> vl;

#define nl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i = a; i < b; i++)

const int DEBUG = true;

vi depth, numDepths, par, taken;


vi height;
vi bestchild;
vvi child;

int n;
int ans = 0;
int numones = 0;

int getheight(int cur){
    if(height[cur] != -1) return height[cur];
    height[cur] = 1;
    for(int i : child[cur]){
        if(1 + getheight(i) > height[cur]){
            height[cur] = 1 + getheight(i);
            bestchild[cur] = i;
        }
    }

    return height[cur];
}
// void solve(int cur, bool onpath)
// {
//     if(!onpath){
//         if(getheight(cur) == 1) numones++;
//         else{
//             ans++;
//         }
//     }

//     for(int c : child[cur]){
//         if(c == bestchild[cur]) continue;
//         solve(c, false);
//     }
    
//     if(bestchild[cur] != -1){
//         solve(bestchild[cur], true);
//     }

// }


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tt;
    cin >> tt;
    while(tt--)
    {
        cin >> n;
        par = vi(n);
        child = vvi(n);
        height = vi(n, -1);
        bestchild = vi(n, -1);
        ans = 0;
        numones = 0;
        for(int i = 1; i < n; i++){
            cin >> par[i];
            par[i]--;
            child[par[i]].push_back(i);
        }
        int mxht = 0;
        vi freq;
        for(int i = 0; i < n; i++){
            mxht = max(mxht, getheight(i));
            while((int)freq.size() - 1 < mxht){
                freq.push_back(0);
            }
            freq[getheight(i)]++;
        }
        int l = mxht, r = mxht;
        while(r > 0){
            while(l > 0 && freq[l] == freq[r]){
                l--;
            }
            if(r - l >= freq[r]){
                ans += freq[r];
                for(int i = 1; i <= r; i++){
                    freq[i] -= freq[r];
                }
                r = l;
            }
            else{
                ans++;
                freq[r] = 0;
                r--;
            }
        }
        // if(numones > 0) ans++;
        cout << ans << nl;
    }
}
