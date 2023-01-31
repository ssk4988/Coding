#include <bits/stdc++.h>
using namespace std;
using ll = long long;
long long dp[70][2];
long long calculate(long long n)
{
	memset(dp, 0, sizeof dp);
	long long count = 0;
	long long prevValue = 0;
	long long currLen = 0;
	vector<pair<int, int>> regions; // color, length;
	while (n)
	{
		if ((n & 1) == prevValue)
			currLen++;
		else
		{
			if (currLen)
				regions.push_back(make_pair(prevValue, currLen));
			prevValue ^= 1;
			currLen = 1;
		}
		n >>= 1;
	}
	regions.push_back(make_pair(prevValue, currLen));
	if (regions[0].second >= 2)
	{
		dp[0][1 - regions[0].second] = 2;
	}
	if (regions[0].second == 1)
	{
		dp[0][1 - regions[0].second] = 1;
	}
	// 0 case
	for (int i = 1; i < regions.size(); i++)
	{
		// dp[i][regions[i].second] = 
		dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + min(regions[i-1].second, 2)) + min(2, regions[i].second);
		dp[i][1] = min(dp[i - 1][1] + 2, dp[i - 1][0] + min(2, regions[i].second));
	}
	return dp[regions.size() - 1][prevValue];
	// if (prevValue == 0) cout << "Fuck bloody fuck";
}
pair<long long, long long> countBits(long long n)
{
	long long count = 0;
	long long k = 0;
	while (n)
	{
		count += n & 1;
		k++;
		n >>= 1;
	}
	return make_pair(count, k - 1);
}
int calculate2(long long num)
{
	long long topsum = 0;
	long long bottomsum = 0;
	queue<pair<long long, int>> q;
	q.push(make_pair(num, 0));
	while (q.size())
	{
		pair<long long, int> temp = q.front();
		q.pop();
		pair<long long, long long> a = countBits(temp.first);
		if (a.first == 1)
			return temp.second + 1;
		if (a.first == 0)
			return temp.second;
		long long topsum = abs((1 << a.second) - temp.first);
		long long bottomsum = abs((1 << (a.second + 1)) - temp.first);
		q.push(make_pair(topsum, temp.second + 1));
		q.push(make_pair(bottomsum, temp.second + 1));
	}
}

int main()
{
	// long long N; cin >> N;
	// for (int i = 0; i < N; i++) {
	// 	long long temp; cin >> temp;
	// 	cout << calculate(abs(temp)) << endl;
	// }
	int lim = 50;
	for (ll i = 0; i < 1000000LL && lim; i++)
	{
		if (calculate(i) != calculate2(i))
		{
			cout << i << "\n";
			lim--;
		}
	}
}
