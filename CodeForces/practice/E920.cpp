#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<vector>
#include<set>
#include<string>
#include<cmath>
#include<cstring>
#define F first
#define S second
#define ll long long
#define pb push_back
#define pm make_pair
using namespace std;
typedef pair<int,int> PII;
const int MAX = 2e5 + 5;
map<int,bool> mp[MAX];
vector<int> vv,ans;
int bfs(int x) {
	int res = 0;
	queue<int> q;
	q.push(x);
	while(q.size()) {
		int cur = q.front();q.pop();
		res++;
//int up = vv.size(); This cannot be written here, because size is dynamic.
		for(int i = 0; i<(int)vv.size(); i++) {
			int v = vv[i];
			if(mp[cur].count(v) == 0) {
				swap(vv[i],vv.back());//Used to realize the erase operation of set and reduce constants. 
				vv.pop_back();//Used to realize the erase operation of set 
				i--;
				q.push(v);
			}
		}
	}
	return res;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i = 1; i<=n; i++) vv.pb(i);
	for(int x,y,i = 1; i<=m; i++) {
		scanf("%d%d",&x,&y);
		mp[x][y]=1;
		mp[y][x]=1;
	}
	while(!vv.empty()) {
		int v = vv.back();vv.pop_back();
		int cnt = bfs(v);
		ans.push_back(cnt);
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(int i = 0; i<(int)ans.size(); i++) {
		printf("%d ",ans[i]);
	}

	return 0;
}