#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int N = 20;
int dp[N+1][1 << N][2][2];
// len, mask, block left, block right
int mexbuffer[1000];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, 0, sizeof dp);
    memset(mexbuffer, 0, sizeof mexbuffer);
    // base case
    rep(i, 0, 2) {
        rep(j, 0, 2) dp[0][0][i][j] = 0;
    }
    rep(len, 1, N+1) {
        rep(mask, 0, 1 << len) {
            rep(left, 0, 2) {
                rep(right, 0, 2) {
                    int mx = 0;
                    rep(b, 0, len) {
                        int bit = (mask >> b) & 1;
                        if(bit) {
                            int tran = dp[len][mask ^ (1 << b)][left][right];
                            mexbuffer[tran] = 1;
                            mx = max(mx, tran);
                            tran = 0;
                            if(b) {
                                int pref = mask & ((1 << b)-1);
                                tran ^= dp[b][pref][left][0];
                            }
                            if(b+1 < len) {
                                int suff = mask >> (b+1);
                                tran ^= dp[len-(b+1)][suff][0][right];
                            }
                            mexbuffer[tran] = 1;
                            mx = max(mx, tran);
                        } else {
                            if((b == 0 && left) || (b+1 == len && right)) {
                                // cant do
                            } else {
                                int tran = 0;
                                if(b) {
                                    int pref = mask & ((1 << b)-1);
                                    tran ^= dp[b][pref][left][1];
                                }
                                if(b + 1 < len) {
                                    int suff = mask >> (b+1);
                                    tran ^= dp[len-(b+1)][suff][1][right];
                                }
                                mexbuffer[tran] = 1;
                                mx = max(mx, tran);
                            }
                        }
                    }
                    int mex = 0;
                    while(mexbuffer[mex]) mex++;
                    dp[len][mask][left][right] = mex;
                    // if(len < 4) cerr << mex << endl;
                    rep(i, 0, mx+1) mexbuffer[i] = 0;
                }
            }
        }
    }

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int r; cin >> r;
        vi lens, masks, lefts, rights;
        lens.push_back(0), masks.push_back(0), lefts.push_back(0), rights.push_back(0);
        rep(i, 0, r) {
            int mask = 0;
            string s; cin >> s;
            rep(j, 0, 3) {
                mask *= 2;
                mask += s[j] == 'I';
            }
            if(mask == 6) mask = 3;
            if(mask == 3 || mask == 7) {
                masks.back() ^= (mask == 7) << lens.back();
                lens.back()++;
            }
            else{
                if(mask == 2) rights.back() = 1;
                lens.push_back(0), masks.push_back(0), lefts.push_back(0), rights.push_back(0);
                if(mask == 2) lefts.back() = 1;
            }
        }
        int ans = 0;
        rep(i, 0, sz(lens)) {
            if(lens[i] == 0) continue;
            ans ^= dp[lens[i]][masks[i]][lefts[i]][rights[i]];
        }
        cout << (ans == 0 ? "Second" : "First") << "\n";
    }

    return 0;
}
