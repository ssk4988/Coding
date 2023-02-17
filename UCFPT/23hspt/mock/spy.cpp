#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vi> ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            grid[i][j] = str[j];
        }
    }
    map<int, int> freq;
    rep(i, 0, n){
        rep(j, 0, m){
            int cnt = 0;
            if(grid[i][j] != 'P') continue;
            rep(k, 0, 4){
                int i1 = i + ds[k][0], j1 = j + ds[k][1];
                if(i1 < 0 || j1 < 0 || i1 >= n || j1 >= m) continue;
                if(grid[i1][j1] == '#') cnt++;
            }
            freq[cnt]++;
        }
    }
    int maxans = 0, minans = 0;
    for(auto p : freq){
        if(p.first == 1){
            maxans += p.second;
        }
        else if(p.first > 1){
            maxans += p.second;
            minans += p.second;
        }
    }
    cout << minans << " " << maxans << "\n";
}