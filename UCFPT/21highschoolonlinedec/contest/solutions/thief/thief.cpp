#include <bits/stdc++.h>

using namespace std;

// thief.cpp by Asir Alam
// this solution follows an iterative dynamic programming approach

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);

  // for every museum / test case loop
  int NUM_CASES; cin >> NUM_CASES;
  for (int T = 1; T <= NUM_CASES; T++)
  {
    int p; cin >> p;    // # of paintings
    vector<int> val(p); // painting values

    for (int i = 0; i < p; i++)
      cin >> val[i];

    // dynamic programming tabulation:

    // dp[i].first will contain the sum of the values of all the
    // paintings taken if we consider the first i paintings

    // dp[i].second will keep track of the most valuable
    // painting not taken so far

    // so the answer to the first i paintings will be
    // = dp[i].first + dp[i].second
    vector<pair<int, int>> dp(p);

    // initialize base case dp[0]:
    // if there exists only the first painting,
    // we always want to take it, and we have no
    // painting left to use the bolt-cutter on
    dp[0] = {val[0], 0};

    // we also want to initialize dp[1] if p > 1
    // because otherwise, dynamic programming will
    // attempt to access dp[-1], which is an invalid index
    if (p > 1)
    {
      // dp[1] considers only the first two elements
      // so we simply want to take the larger of the two
      dp[1].first = max(val[0], val[1]);

      // whichever we did not pick will be the one to use the bolt-cutter on
      dp[1].second = (dp[1].first == val[1]) ? val[0] : val[1];
    }

    // iterate over all paintings, starting i = 2
    for (int i = 2; i < p; i++)
    {
      // if we choose to take painting i, dp[i].second = take_boltval
      int take_boltval = max(dp[i - 2].second, val[i - 1]);

      // if we choose to leave painting i, dp[i].second = leave_boltval
      int leave_boltval = max(dp[i - 1].second, val[i]);

      // if taking painting i results in a higher
      // overall profit than not taking painting i,
      // we take it
      if (val[i] + dp[i - 2].first > dp[i - 1].first)
        dp[i] = {val[i] + dp[i - 2].first, take_boltval};

      // if less overall profict, we leave it
      else if (val[i] + dp[i - 2].first < dp[i - 1].first)
        dp[i] = {dp[i - 1].first, leave_boltval};

      // if same overall profit, we choose dp[i].second
      // based on the higher "bolt-cutter" value (boltval)
      else
        dp[i] = {dp[i - 1].first, max(take_boltval, leave_boltval)};
    }

    // finally we add the main profit and the bolt-cutter profit
    cout << dp[p - 1].first + dp[p - 1].second << "\n";    
  }
  return 0;
}
