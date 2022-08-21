/*
  quine.cpp
  Is the Name of This Problem, MCPC 2012 Problem D
  C++ solution by Gabriel Foust
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ifstream fin( "quine.in" );

int main()
{
  string line;

  while (getline( fin, line ) && line != "END")
  {
    cerr << "ECHO (" << line.size() << "): " << line << endl;
    if (line.length() >= 5 &&
        line[0] == '"' &&
        line[line.length()/2] == '"' &&
        line[line.length()/2 + 1] == ' ')
    {
      string A= line.substr( 1,                   line.length()/2 - 1);
      string B= line.substr( line.length()/2 + 2, line.length()/2 - 1);
      if (A == B && A.find( "\"" ) == string::npos)
        cout << "Quine(" << A << ")" << endl;
      else
        cout << "not a quine" << endl;
    }
    else
      cout << "not a quine" << endl;
  }

  return 0;
}
