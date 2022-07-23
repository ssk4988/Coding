#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int oo = -1^1<<31;

int maxw = 1000000000-10;

vector<pair<int, pair<int, int>>> edges;
vector<vector<pair<int, int>>> graph;

void genGraph(int n, int m){
    edges = vector<pair<int, pair<int, int>>>(m);
    graph = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(0));

    for(int i = 1; i < n; i++){
        int u = i;
        int v = rand()%i;
        int w = (rand()%maxw)+1;
        edges[i-1] = make_pair(u, make_pair(v, w));
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    for(int i = n-1; i < m; i++){
        int u = rand()%n;
        int v = rand()%n;
        int w = (rand()%maxw)+1;
        edges[i] = make_pair(u, make_pair(v, w));
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
}


int main(){
    cin.tie(0)->sync_with_stdio(0);
    int numgen = 3;
    int maxn = 1000;
    int maxm = 10000;
    srand(time(0));
    for(int tn = 0; tn < numgen; tn++){
        int n = (rand() % maxn) + 1;
        int m = min(n + (rand() % (n*5)), maxm) + 1;
        cout << n << " " << m << endl;
        genGraph(n, m);
        for(auto [u, p] : edges){
            auto [v, w] = p;
            cout << u+1 << " " << v+1 << " " << w << "\n";
        }
    }
}