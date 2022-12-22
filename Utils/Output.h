#include <iostream>
#include <string>

using namespace std;

class Output
{
public:
  static void showError(string, bool fatal = true);
  static void showSuccess(string);
};

void Output::showError(string err, bool fatal)
{
  if (fatal)
    throw("\x1B[31Error: " + err + "\033[0m");

  cout << "\x1B[33Warn: " + err + "\033[0m";
}

void Output::showSuccess(string msg)
{
  cout << "\x1B[32" + msg + "\033[0m";
}