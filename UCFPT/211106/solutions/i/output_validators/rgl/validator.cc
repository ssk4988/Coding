#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "validator.h"

int main(int argc,char **argv){
  if (argc<3 or argc>4){
    fprintf(stderr,"usage: %s testcase.in testcase.ans [feedback] <team.out",argv[0]);
    return (int) judge_error;
  }
  if (argc>3){
    if (not freopen((std::string(argv[3])+"/feedback.txt").c_str(),"w",stdout)){
      fprintf(stderr,"failed to open feedback.txt: %s", strerror(errno));
      return (int) judge_error;
    }
  }

  std::ifstream canonical_input(argv[1]);
  std::ifstream canonical_output(argv[2]);
  std::istream &team_output(std::cin);
  return (int) validate(canonical_input,canonical_output,team_output);
}
