#include <unordered_map>/*{{{*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;/*}}}*/

#include "validator.h"

vector<string> tokens(istream &from){
  vector<string> res;
  for (string s; from>>s; res.push_back(s));
  return res;
}

vector<vector<int64_t>> pyramid(vector<string> from,uint64_t const n){
  vector<vector<int64_t>> rows(n);
  for (uint64_t i=0,p=0; i<n; i++){
    rows[i].resize(i+1);
    for (uint64_t j=0; j<=i; j++,p++){
      stringstream ss(from[p]);
      if (not (ss>>rows[i][j])){
        cout<<"failed to read token #"<<p+1<<" as an integer: \""<<from[p]<<"\""<<endl;
        return {};
      }
      if (not (1<=rows[i][j] and rows[i][j]<=1000'000'000ll)){
        cout<<"cell value "<<rows[i][j]<<" is not in bounds"<<endl;
        return {};
      }
    }
  }
  return rows;
}

JudgeCode validate(
    istream &canonical_input,
    istream &canonical_output,
    istream &team_output){

  // Read input.
  uint64_t n,s; assert(canonical_input>>n>>s);
  assert(1 <= n and n <= 20ll);
  assert(1 <= s and s <= 1'000'000'000ll);

  // Read answers.
  auto const judge_tokens=tokens(canonical_output);
  auto const team_tokens=tokens(team_output);

  bool const judge_impossible=(judge_tokens==vector<string>{"impossible"});
  bool const team_impossible=(team_tokens==vector<string>{"impossible"});

  if (team_impossible){
    if (judge_impossible){
      return correct;
    }else{
      cout<<"team answer is \"impossible\" but judge has an answer."<<endl;
      return wrong_answer;
    }
  }

  if (team_tokens.size()<(n*(n+1)/2)){
    cout<<"too few tokens from team: expected "<<n*(n+1)/2<<", got "<<team_tokens.size()<<endl;
    return wrong_answer;
  }

  if (not judge_impossible){
    auto const judge_pyramid=pyramid(judge_tokens,n);
    if (judge_pyramid.empty()){
      return judge_error;
    }
  }
  auto const team_pyramid=pyramid(team_tokens,n);
  if (team_pyramid.empty()){
    return wrong_answer;
  }

  for (uint64_t i=0; i<n; i++){
    for (uint64_t j=0; j<=i; j++){
      if (i==0 and j==0 and (uint64_t) team_pyramid[i][j]!=s){
        cout<<"first number output by team is not the top cell."<<endl;
        return wrong_answer;
      }
      if (i+1<n and team_pyramid[i][j]!=team_pyramid[i+1][j]+team_pyramid[i+1][j+1]){
        cout<<"cell "<<i+1<<":"<<j+1<<" != cell "<<i+2<<":"<<j+1<<" + cell "<<i+2<<":"<<j+2<<endl;
        return wrong_answer;
      }
    }
  }

  if (judge_impossible){
    cout<<"judge answer is \"impossible\" but team found an answer."<<endl;
    return judge_error;
  }else{
    return correct;
  }
}
