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

const int MAXN = 1000;
vpi adj[MAXN];
vi db[MAXN];
const int b7 = 1 << 7;
const int target = b7 - 1;
int rl[MAXN], db2[MAXN];
int dist[MAXN][b7];
bool visited[MAXN][b7];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k, m; cin >> n >> m >> k;
    rep(i, 0, m){
        int a, b, t; cin >> a >> b >> t;
        a--,b--;
        adj[a].pb({b, t});
        adj[b].pb({a, t});
    }
    rep(i, 0, k){
        int c, d; cin >> c >> d;
        db[c - 1].pb(d-1);
    }
    srand(time(NULL));
    int minans = INT_MAX;
    
    rep(times, 0, 1000){
        rep(i, 0, n){
            rl[i] = rand() % 7;
        }
        rep(i, 0, n){
            db2[i] = 0;
            for(int j : db[i]){
                db2[i] |= 1 << rl[j];
            }
            rep(j, 0, b7){
                dist[i][j] = INT_MAX;
                visited[i][j] = false;
            }
        }
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        dist[0][db2[0]] = 0;
        pq.push({dist[0][db2[0]], 0 * b7 + db2[0]});
        while(!pq.empty()){
            auto [d, st] = pq.top();
            pq.pop();
            int node = st / b7, seen = st % b7;
            if(visited[node][seen]) continue;
            visited[node][seen] = true;
            if(dist[node][seen] > minans || seen == target) 
                break;
            for(auto [newnode, w] : adj[node]){
                int newseen = seen | db2[newnode];
                if(!visited[newnode][newseen] && dist[newnode][newseen] > dist[node][seen] + w){
                    dist[newnode][newseen] = dist[node][seen] + w;
                    pq.push({dist[newnode][newseen], newnode * b7 + newseen});
                }
            }
        }
        int best = INT_MAX;
        rep(i, 0, n){
            best = min(best, dist[i][target]);
        }
        minans = min(best, minans);
    }
    if(minans == INT_MAX) minans = -1;
    cout << minans << "\n";
    
    return 0;
}