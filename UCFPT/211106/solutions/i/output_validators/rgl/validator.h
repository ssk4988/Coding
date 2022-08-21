#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <istream>

enum JudgeCode:int{
  judge_error=1,
  correct=42,
  wrong_answer=43,
};

JudgeCode validate(
  std::istream &canonical_input,
  std::istream &canonical_output,
  std::istream &team_output);

#endif /* VALIDATOR_H */
