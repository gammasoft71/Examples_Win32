#include <cstdint>
#include <string>
#include <Windows.h>

using namespace std;

int main() {
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Hello ", 6, nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"World!\n", 7, nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Enter your name: ", 17, nullptr, nullptr);
  wstring name(1024, 0);
  int32_t numberOfCharsRead = 0;
  ReadConsole(GetStdHandle(STD_INPUT_HANDLE), (LPVOID)name.c_str(), 1024, (LPDWORD)&numberOfCharsRead, nullptr);
  name.resize(numberOfCharsRead-2);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"Good day, ", 10, nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), name.c_str(), static_cast<int32_t>(name.length()), nullptr, nullptr);
  WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"!\n", 2, nullptr, nullptr);
}

// This code produces the following output:
//
// Hello World!
// Enter your name: James
// Good day, James!
